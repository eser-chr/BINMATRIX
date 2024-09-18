#ifndef H_MATRIX
#define H_MATRIX
#include <stdint.h>

namespace matrix{

    class BinaryMatrix{
        BinaryMatrix(int dimensions, int* lengths);
        BinaryMatrix(int dimensions, int* lengths, uint8_t* data);
        
        
        void get_coords_of_index(int& index, int* coords);
        void get_index_of_coords(int& index, int* coords);
        
        bool get_point(int* coords);
        bool get_point(int index);

        void set_point(bool val, int* coords);
        void set_point(bool val, int index);

        bool* get_neighbors(int *coords);
        bool* get_negihbors(int index);

        int count_negihbors(int* coords);
        int count_neighbors(int index);


        private:
            int m_dimensions;
            int* m_lengths;
            int* m_cumlengths;
            int m_total_voxels;
            int m_total_bytes;
            uint8_t* m_data; 
    };


};


#endif