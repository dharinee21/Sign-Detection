#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;

int main()
{
     PaletteEntry palette[256];
     bool   result = false;
     int  bit_depth = CV_ELEM_SIZE1(m_type)*8;
-    int  src_pitch = (m_width*m_bpp*bit_depth/8 + 7)/8;
+    size_t  src_pitch = (((size_t)m_width)*m_bpp*bit_depth/8 + 7)/8;
     int  nch = CV_MAT_CN(m_type);
     int  width3 = m_width*nch;
     int  i, x, y;
    return 0;
}
