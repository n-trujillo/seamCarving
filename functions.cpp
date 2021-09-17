#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

#define INFO(X) cout << "[INFO] ("<<__FUNCTION__<<":"<<__LINE__<<") " << #X << " = " << X << endl;

using std::cout;
using std::endl;
using std::string;

Pixel** createImage(int width, int height) {
  
  // Create a one dimensional array on the heap of pointers to Pixels 
  //    that has width elements (i.e. the number of columns)
  Pixel** image = new Pixel*[width];
  
  bool fail = false;
  
  for (int i=0; i < width; ++i) { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    image[i] = new Pixel[height];
    
    if (image[i] == nullptr) { // failed to allocate
      fail = true;
    }
  }
  
  if (fail) { // if any allocation fails, clean up and avoid memory leak
    // deallocate any arrays created in for loop
    for (int i=0; i < width; ++i) {
      delete [] image[i]; // deleting nullptr is not a problem
    }
    delete [] image; // dlete array of pointers
    return nullptr;
  }
  
  // initialize cells
  //cout << "Initializing cells..." << endl;
  for (int row=0; row<height; ++row) {
    for (int col=0; col<width; ++col) {
      //cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = { 0, 0, 0 };
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel** image, int width) {
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i=0; i<width; ++i) {
    delete [] image[i]; // delete each individual array placed on the heap
  }
  delete [] image;
  image = nullptr;
}

int* createSeam(int length) {
    // TODO(student): create a seam
    int* seam = new int[length];
    for(int i = 0; i < length; i ++) {
      seam[i] = 0;
    }

    return seam;

    INFO(length);
}

void deleteSeam(int* seam) {
    // TODO(student): delete a seam
    delete[] seam;

    INFO(seam);
}

bool loadImage(string filename, Pixel** image, int width, int height) {
    // TODO(student): load an image

  //////////////////////////////////////

  // declare/define and open input file stream
  std::ifstream ifs (filename);
  
  // check if input stream opened successfully
  if (!ifs.is_open()) {
    cout << "Error: failed to open input file - " << filename;
    return false;
  }
  
  // get type from preamble
  string type;
  ifs >> type; // should be P3
  if ((toupper(type.at(0)) != 'P') || (type.at(1) != '3') || type.size() > 2) { // check that type is correct
    cout << "Error: type is " << type << " instead of P3";
    return false;
  }
  
  // get width (w) and height (h) from preamble
  int w = 0, h = 0;
  ifs >> w >> h;

  if (ifs.fail() == true) {
    cout << "Error: read non-integer value";
    return false;
  }


  if (w != width) { // check that width matches what was passed into the function
    cout << "Error: input width (" << width << ") does not match value in file (" << w << ")";
    return false;

  }
  if (h != height) { // check that height matches what was passed into the function
    cout << "Error: input height (" << height << ") does not match value in file (" << h << ")";
    return false;
  }
  
  // get maximum value from preamble
  int colorMax = 0;
  ifs >> colorMax;

  if (ifs.fail()) {
    cout << "Error: read non-integer value";
    return false;
  }

  if (colorMax > 255 || colorMax < 0) {
    cout << "Error: invalid color value " << colorMax;
    return false;
  }


  // TODO(student): get RGB pixel values
  for (int row = 0; row < height; row ++) { // go through each row
    for (int col = 0; col < width; col ++) { // go through each col

    int imgValR = 0;
    int imgValG = 0;
    int imgValB = 0;

    ifs >> imgValR;
      if (ifs.fail()) {
        cout << "Error: read non-integer value";
        return false;
      }

      if (imgValR < 0) {
        cout << "Error: invalid color value " << imgValR;
        return false;
      }

      if (ifs.eof()) {
        cout << "Error: not enough color values";
        return false;
      }

      if (imgValR > colorMax || imgValR > 255) {
        cout << "Error: invalid color value " << imgValR;
        return false;
      }


    ifs >> imgValG;
      if (ifs.fail()) {
        cout << "Error: read non-integer value";
        return false;
      }

      if (imgValG < 0) {
        cout << "Error: invalid color value " << imgValG;
        return false;
      }

      if (ifs.eof()) {
        cout << "Error: not enough color values";
        return false;
      }

      if (imgValG > colorMax || imgValG > 255) {
        cout << "Error: invalid color value " << imgValG;
        return false;
      }


    ifs >> imgValB;

      if (ifs.eof() && ifs.fail()) {
          cout << "Error: not enough color values";
          return false;
        }

      if (ifs.fail()) {
        cout << "Error: read non-integer value";
        return false;
      }

      if (imgValB < 0) {
        cout << "Error: invalid color value " << imgValB;
        return false;
      }

      if (imgValG > colorMax || imgValB > 255) {
        cout << "Error: invalid color value " << imgValB;
        return false;
      }



    // assign column major
    image[col][row].r = imgValR; // set imgValR to r sruct
    image[col][row].g = imgValG; // set imgValG to g struct
    image[col][row].b = imgValB; // set imgValB to b stuct

  }// end of for
} // end of for

  // after iterating check and see if there are extra values
  int check;
  ifs >> check;
  if (ifs.fail()) {
    return true; // if there fails to be any extra values then we are good
  } else {
    cout << "Error: too many color values";
    return false;
  }

  //////////////////////////////////////

    //INFO(filename);
    //INFO(image);
    //INFO(width);
    //INFO(height);
  return true;
}

bool outputImage(string filename, Pixel** image, int width, int height) {
    // TODO(student): output an image

    // using code from image manipulation lab

    /////////////////////////////////

  // TODO(student): declare/define and open output file stream

  std::ofstream outFS; // Output file stream

  // Open file
  outFS.open(filename);

  // TODO(student): check if output stream opened successfully
  if (!outFS.is_open()) {
    cout << "Error: failed to open output file " << filename;
    return false;
  }

  // Write to file

  // TODO(student): output preamble
  outFS << "P3" << endl;
  outFS << width << " " << height << endl;
  outFS << "255" << endl;

  // TODO(student): output pixels

  for (int row = 0; row < height; row ++) { // go through each row
    for (int col = 0; col < width; col ++) { // go through each col

      outFS << image[col][row].r << " ";
      outFS << image[col][row].g << " ";
      outFS << image[col][row].b << " ";

    }

    outFS << endl; // after going through all columns end line and go next row

  }

  // Done with file, so close
  outFS.close();

    /////////////////////////////////



    //INFO(filename);
    //INFO(image);
    //INFO(width);
    //INFO(height);
  return true;
}

int energy(Pixel** image, int column, int row, int width, int height) { 
    // TODO(student): compute the energy of a pixel

  int XRdiff = 0;
  int XGdiff = 0;
  int XBdiff = 0;

  int YRdiff = 0;
  int YGdiff = 0;
  int YBdiff = 0;

  int deltaY = 0;
  int deltaX = 0;

  int totalEnergy = 0;

  char colPos = '\0';
  char rowPos = '\0';

// NO BOARDERS
  if (column >= 1 && column <= width - 1) {
    colPos = 'N';
  }

  if (row >= 1 && row <= height - 1) {
    rowPos = 'N';
  }

// BOARDERS
  // left boarder
  if (column == 0) {
    colPos = 'L';
  }

  // right boarder
  if (column == (width - 1)) { 
    colPos = 'R';
  }

  // top boarder
  if (row == 0) {
    rowPos = 'T';

  }

  // bottom boarder
  if (row == (height - 1)) {
    rowPos = 'B';
  }


int rowMod = 1;
int colMod = 1;

  // special case checks
  if (height == 1) {
    rowMod = 0;
  }

  if (width == 1) {
    colMod = 0;
  }



  switch(colPos) { // use colPos to determine col calculation

    case 'N' : // non boarder
      XRdiff = abs(image[column + colMod][row].r - image[column - colMod][row].r);
      XGdiff = abs(image[column + colMod][row].g - image[column - colMod][row].g);
      XBdiff = abs(image[column + colMod][row].b - image[column - colMod][row].b);

      deltaX = (XRdiff*XRdiff) + (XGdiff*XGdiff) + (XBdiff*XBdiff);
      break;

    case 'L' : // left col
      XRdiff = abs(image[column + colMod][row].r - image[width - 1][row].r); // width - 1 is right boarder
      XGdiff = abs(image[column + colMod][row].g - image[width - 1][row].g);
      XBdiff = abs(image[column + colMod][row].b - image[width - 1][row].b);

      deltaX = (XRdiff*XRdiff) + (XGdiff*XGdiff) + (XBdiff*XBdiff);
      break;

    case 'R' : // right col
      XRdiff = abs(image[0][row].r - image[column - colMod][row].r); // 0 is left boarder
      XGdiff = abs(image[0][row].g - image[column - colMod][row].g); // column - 1 is left neighbor
      XBdiff = abs(image[0][row].b - image[column - colMod][row].b);

      deltaX = (XRdiff*XRdiff) + (XGdiff*XGdiff) + (XBdiff*XBdiff);
      break;

    default:
      break;
  }

  switch(rowPos) { // use rowPos to determine row calculation

    case 'N': // non boarder
      YRdiff = abs(image[column][row + rowMod].r - image[column][row - rowMod].r);
      YGdiff = abs(image[column][row + rowMod].g - image[column][row - rowMod].g);
      YBdiff = abs(image[column][row + rowMod].b - image[column][row - rowMod].b);

      deltaY = (YRdiff*YRdiff) + (YGdiff*YGdiff) + (YBdiff*YBdiff);
      break;

    case 'T' : // top row
      YRdiff = abs(image[column][row + rowMod].r - image[column][height - 1].r); // hight - 1 is bottom boarder
      YGdiff = abs(image[column][row + rowMod].g - image[column][height - 1].g);
      YBdiff = abs(image[column][row + rowMod].b - image[column][height - 1].b);

      deltaY = (YRdiff*YRdiff) + (YGdiff*YGdiff) + (YBdiff*YBdiff);
      break;

    case 'B' : // bottom row
      YRdiff = abs(image[column][0].r - image[column][row - rowMod].r); // 0 is top boarder
      YGdiff = abs(image[column][0].g - image[column][row - rowMod].g); // row - 1 is upper neighbor
      YBdiff = abs(image[column][0].b - image[column][row - rowMod].b);
      deltaY = (YRdiff*YRdiff) + (YGdiff*YGdiff) + (YBdiff*YBdiff);
      break;

    default :
      break;
  }


  // add delta X and Y
  totalEnergy = deltaX + deltaY;
  return totalEnergy;



    //INFO(image);
    //INFO(column);
    //INFO(row);
    //INFO(width);
    //INFO(height);
  return 0;
}

int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {
    // TODO(student): load a vertical seam

    // set seam for the first row to the staring col
    seam[0] = start_col;

    // initialize total enerygy to star pixel energy
    int totalEnergy = energy(image, start_col, 0, width, height);


    int column = start_col; // initialize column postition
    // iterate through all the rows

    if (height > 1) { // only applies to images that are longer than 1 row
      for (int row = 1; row < height; row ++) { // start at next rom

        // prevent over indexing
        bool calcPlus = true;
        bool calcMinus = true;

        int plusMod = 1;
        int minusMod = 1;

        if (column == 0) {
          calcMinus = false; // DO NOT colMinus
          minusMod = 0;

        }

        if (column == (width - 1)) {
          calcPlus = false; // DO NOT colPlus
          plusMod = 0;
        }

        // calcualte energy of each next possible col
        int colPlusVal = energy(image, (column + plusMod), row, width, height);
        int colStayVal = energy(image, column, row, width, height);
        int colMinusVal = energy(image, (column - minusMod), row, width, height);

        // get the minimum of the three
        int minEnergyVal = 0;
        int minEnergyPos = 0;

        // decide on the choice

        minEnergyVal = colStayVal; // forward option always exists so it will be default
        minEnergyPos = column; // pos is just simply the col

        if ((colPlusVal < minEnergyVal) && calcPlus) { // if calcPlus is false then this position does not exists and will not be considered
          minEnergyVal = colPlusVal;
          minEnergyPos = column + 1;
        }

        if ((colMinusVal < minEnergyVal) && calcMinus) { // if calcMinus is flase then this postition does not exist and will not be considered
          minEnergyVal = colMinusVal;
          minEnergyPos = column - 1;
        }

        // set smallest to the according vlaue in seam
        seam[row] = minEnergyPos;
        column = minEnergyPos; // update column

        // add smallest to total energy
        totalEnergy = totalEnergy + minEnergyVal;

      }
    }

    return totalEnergy;

    //INFO(image);
    //INFO(start_col);
    //INFO(width);
    //INFO(height);
    //INFO(seam);

  return 0;
}

int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) {
    // TODO(student): load a horizontal seam


    // set seam for the first row to the staring col
    seam[0] = start_row;

    // initialize total enerygy to star pixel energy
    int totalEnergy = energy(image, 0, start_row, width, height);


    int row = start_row; // initialize column postition
    // iterate through all the rows

    if (width > 1) { // only applies to images that are longer than 1 row
      for (int col = 1; col < width; col ++) { // start at next rom

        // prevent over indexing
        bool calcPlus = true;
        bool calcMinus = true;

        int plusMod = 1;
        int minusMod = 1;

        if (row == 0) {
          calcMinus = false; // DO NOT colMinus
          minusMod = 0;

        }

        if (row == (height - 1)) {
          calcPlus = false; // DO NOT colPlus
          plusMod = 0;
        }

        // calcualte energy of each next possible col
        int rowPlusVal = energy(image, col, (row + plusMod), width, height);
        int rowStayVal = energy(image, col, row, width, height);
        int rowMinusVal = energy(image, col, (row - minusMod), width, height);

        // get the minimum of the three
        int minEnergyVal = 0;
        int minEnergyPos = 0;

        // decide on the choice

        minEnergyVal = rowStayVal; // forward option always exists so it will be default
        minEnergyPos = row; // pos is just simply the col

        if ((rowMinusVal < minEnergyVal) && calcMinus) { // if calcMinus is flase then this postition does not exist and will not be considered
          minEnergyVal = rowMinusVal;
          minEnergyPos = row - 1;
        }

        if ((rowPlusVal < minEnergyVal) && calcPlus) { // if calcPlus is false then this position does not exists and will not be considered
          minEnergyVal = rowPlusVal;
          minEnergyPos = row + 1;
        }



        // set smallest to the according vlaue in seam
        seam[col] = minEnergyPos;
        row = minEnergyPos; // update column

        // add smallest to total energy
        totalEnergy = totalEnergy + minEnergyVal;

      }
    }

    return totalEnergy;


    INFO(image);
    INFO(start_row);
    INFO(width);
    INFO(height);
    INFO(seam);
  return 0;
}

int* findMinVerticalSeam(Pixel** image, int width, int height) {
    // TODO(student): find min vertical seam

    // create potential and candidate seams
    int* potentialSeam = createSeam(height * width); // create a temp seam that has the correct number of rows 
    int* candidateSeam = createSeam(height * width);

    int candidate = loadVerticalSeam(image, 0, width, height, candidateSeam); // update seam and candidate value
    
    for (int col = 1; col < width; col ++) { // start at the next val value and go through the rest

      int potential = loadVerticalSeam(image, col, width, height, potentialSeam);
      // here we write to a temporary seam
      // if this potential becomes candidate then we will copy this potentialSeam to the actual seam

      if (potential < candidate) {
        // update candidate value
        candidate = potential;

        // now update the candidateSeam with the contents of potentialSeam
        for (int i = 0; i < width; i ++) {
          candidateSeam[i] = potentialSeam[i];
        }
      }
    }

    deleteSeam(potentialSeam); // get rid of our temp
    potentialSeam = nullptr; // wipe our pointer

    // dont delete candidate seam or its pointer because it will still be used later

    //INFO(image);
    //INFO(width);
    //INFO(height);

  return candidateSeam; // return the a pointer to the candidate seam // this is the seam that has the smallest energy value
}

int* findMinHorizontalSeam(Pixel** image, int width, int height) {
    // TODO(student): find min horizontal seam

    // create potential and candidate seams
    int* potentialSeamHz = createSeam(height * width); // create a temp seam that has the correct number of rows 
    int* candidateSeamHz = createSeam(height * width);

    int candidate = loadHorizontalSeam(image, 0, width, height, candidateSeamHz); // update seam and candidate value
    
    for (int row = 1; row < height; row ++) { // start at the next val value and go through the rest

      int potential = loadHorizontalSeam(image, row, width, height, potentialSeamHz);
      // here we write to a temporary seam
      // if this potential becomes candidate then we will copy this potentialSeam to the actual seam

      if (potential < candidate) {
        // update candidate value
        candidate = potential;

        // now update the candidateSeam with the contents of potentialSeam
        for (int i = 0; i < height; i ++) {
          candidateSeamHz[i] = potentialSeamHz[i];
        }
      }
    }

    deleteSeam(potentialSeamHz); // get rid of our temp
    potentialSeamHz = nullptr; // wipe our pointer

    // dont delete candidate seam or its pointer because it will still be used later

    //INFO(image);
    //INFO(width);
    //INFO(height);

  return candidateSeamHz; // return the a pointer to the candidate seam // this is the seam that has the smallest energy value




    INFO(image);
    INFO(width);
    INFO(height);
  return nullptr;
}

void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {
    // TODO(student): remove a vertical seam

    for (int row = 0; row < height; row++) { // iterate through all the rows in the vertical seam

      for (int col = verticalSeam[row]; col < width - 1; col++) { // iterate through all the columns

        image[col][row].r = image[col + 1][row].r; // set each col to right nieghbor following the seam col
        image[col][row].g = image[col + 1][row].g;
        image[col][row].b = image[col + 1][row].b;

      }
    }

    //INFO(image);
    //INFO(width);
    //INFO(height);
    //INFO(verticalSeam);
}

void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
    // TODO(student): remove a horizontal seam

    for (int col = 0; col < width; col++) { // iterate through all the rows in the vertical seam

      for (int row = horizontalSeam[col]; row < height - 1; row++) { // iterate through all the columns

        image[col][row].r = image[col][row + 1].r; // set each col to right nieghbor following the seam col
        image[col][row].g = image[col][row + 1].g;
        image[col][row].b = image[col][row + 1].b;

      }
    }


    INFO(image);
    INFO(width);
    INFO(height);
    INFO(horizontalSeam);
}
