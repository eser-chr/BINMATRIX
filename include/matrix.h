#ifndef H_MATRIX
#define H_MATRIX
#include <stdint.h>

namespace matrix{

    class Matrix{
        Matrix(int dimensions, int* lengths);
        Matrix(int dimensions, int* lengths, uint8_t* data);
        
        int* get_coords_of_index();
        int get_index_of_coords();
        
        bool get_point(int* coords);
        bool get_point(int index);

        void set_point(bool val, int* coords);
        void set_point(bool val, int index);



        private:
            int m_dimensions;
            int* lengths;
            uint8_t* data; 
    };


};


#endif