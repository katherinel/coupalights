class CoupaLight {
public: 
        CoupaLight (int, int, int);
        int radius;
        int degree;
        int pixel_num;
        
        void blink(int r, int g, int b);
};

CoupaLight::CoupaLight (int pixel, int radius_l, int degree_l) {
  radius = radius_l;
  degree = degree_l;
  pixel_num = pixel;
}


