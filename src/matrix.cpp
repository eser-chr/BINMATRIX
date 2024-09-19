#include "matrix.h"
#include <stdlib.h>



matrix::BinaryMatrix::BinaryMatrix(int dimensions, int* lengths){
    this->m_dimensions = dimensions;
    this->m_lengths = lengths;

    m_cumlengths = (int*) malloc(dimensions* sizeof(int));
    m_cumlengths[0]=0;
    m_cumlengths[1]=m_lengths[0];
    for(int i=2; i<dimensions; i++){
        m_cumlengths[i] = m_cumlengths[i-1]*m_lengths[i-1];
    }
    m_total_voxels = m_cumlengths[m_dimensions-1]*m_lengths[m_dimensions-1];
    m_total_bytes = (m_total_voxels+7)/8; //ceil division



    m_data = (uint8_t*)calloc(m_total_bytes, sizeof(uint8_t));
}


matrix::BinaryMatrix::BinaryMatrix(int dimensions, int* lengths, uint8_t* data)
    : BinaryMatrix(dimensions, lengths) // Use initializer list to call the other constructor
{
    for(int i=0; i<m_total_bytes; i++){
        m_data[i] = data[i];
    }
}



void matrix::BinaryMatrix::get_index_of_coords(int &index, int* coords){
    index=0;
    for(int i=0; i<m_dimensions; i++){
        index += m_cumlengths[i]*coords[i];
    }
}

void matrix::BinaryMatrix::get_coords_of_index(int &index, int* coords){
    int temp = index;
    for(int i = m_dimensions-1; i >= 0; i--) {
        coords[i] = temp / m_cumlengths[i];
        temp = temp % m_cumlengths[i];
    }

}

bool matrix::BinaryMatrix::get_point(int* coords){
    int index;
    get_index_of_coords(index, coords);
    return get_point(index); 
}

bool matrix::BinaryMatrix::get_point(int index){
    int byte = index/8;
    int bit = index%8;
    return (m_data[byte]>>bit)&1;    
}


void matrix::BinaryMatrix::set_point(bool val, int index){
    int byte = index/8;
    int bit = index%8;
    if(val){
        m_data[byte] |= (1 << bit);
    }else{
        m_data[byte] &= ~(1 << bit);
    }
}

void matrix::BinaryMatrix::set_point(bool val, int* coords){
    int index;
    get_index_of_coords(index, coords);
    set_point(val, index);
}


bool* matrix::BinaryMatrix::get_neighbors(int index){ //Cross neighbors
    int num_of_neighbors = 2*m_dimensions;
    bool* temp = (bool*) malloc(num_of_neighbors* sizeof(bool));
    for(int i = 0; i < m_dimensions; i++){
    int neg_idx = index - i*m_cumlengths[i];
    int pos_idx = index + i*m_cumlengths[i];
    temp[2*i] = (neg_idx >= 0) ? get_point(neg_idx) : 0; // Check bounds
    temp[2*i+1] = (pos_idx < m_total_voxels) ? get_point(pos_idx) : 0; // Check bounds
}

    return temp;    
}


bool* matrix::BinaryMatrix::get_neighbors(int* coords){
    int index;
    get_index_of_coords(index, coords);
    return get_neighbors(index);
}


int matrix::BinaryMatrix::count_neighbors(int index){ //Cross neighbors
    int temp=0;
    for(int i = 0; i<m_dimensions; i++){
        temp += get_point(index-i*m_cumlengths[i]);
        temp += get_point(index+i*m_cumlengths[i]);
    }
    return temp;
}