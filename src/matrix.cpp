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



void matrix::BinaryMatrix::get_index_of_coords(int &index, int* coords){
    index=0;
    for(int i=0; i<m_dimensions; i++){
        index += m_cumlengths[i]*coords[i];
    }
}

void matrix::BinaryMatrix::get_coords_of_index(int &index, int* coords){

}

bool matrix::BinaryMatrix::get_point(int* coords){
    int index;
    get_index_of_coords(index, coords);
    get_point(index); 
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
