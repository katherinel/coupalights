class CoupaBoard {
  
  
public: 
        CoupaBoard ();

        static const int array_width = 65;
        static const int array_depth = 2;
        static int light_array[array_width][array_depth];
        CoupaLight coupa_lights[array_width];
        void add_light(int, int, int);
};



int CoupaBoard::light_array[CoupaBoard::array_width][CoupaBoard::array_depth] =  {
          {80, 305}, {63, 302}, {59, 292}, {56, 280}, {45, 282}, {48, 295}, 
          {53, 308}, {61, 317}, {69, 324}, {52, 325}, {43, 316}, {33, 284}, 
          {36, 327}, {47, 336}, {56, 343}, {67, 346}, {53, 352}, {40, 5}, 
          {52, 5}, {64, 5}, {53, 18}, {41, 21}, {36, 44}, {46, 35}, {57, 29}, 
          {52, 45}, {44, 55}, {72, 46}, {53, 63}, {48, 74}, {46, 88}, {34, 86}, 
          {26, 77}, {45, 102}, {53, 128}, {71, 151}, {52, 144}, {45, 135}, 
          {37, 122}, {47, 155}, {31, 153}, {42, 168}, {54, 172}, {65, 174}, 
          {52, 184}, {30, 205}, {42, 199}, {53, 196}, {65, 194}, {46, 213}, 
          {35, 221}, {28, 234}, {43, 233}, {53, 224}, {63, 218}, {53, 241}, 
          {47, 253}, {46, 267}, {56, 268}, {66, 271}, {74, 252}, {63, 247}, {70, 239}, {82, 226}, {90, 240}
        }; 

void CoupaBoard::add_light (int pixel_num, int radius, int degree) {
  CoupaLight light (pixel_num, radius, degree);
  coupa_lights[pixel_num - 1] = light;  
}

CoupaBoard::CoupaBoard () {
  for (int thisPin = 1; thisPin <= CoupaBoard::array_width; thisPin++){
    add_light(thisPin, CoupaBoard::light_array[thisPin][0], CoupaBoard::light_array[thisPin][1]);
  }
}

