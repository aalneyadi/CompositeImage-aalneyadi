//Ali Alneyadi
#include <iostream>
#include <vector>
#include "bitmap.h"
using namespace std;


// reads in the files and checks if any of them has any problems and saves 
// them to the vector bitmap_images thatis in main function
void process_files(vector<Bitmap>& bitmap_images);


// compares the heihts and widths of two PixelMatrixes and returns true if
// they the same
bool cmp_hw(PixelMatrix a, PixelMatrix b);


// checks to see if there are two valid bitmaps with same dimensions so that
// a composite can be made
bool can_proceed(vector<Bitmap> bitmap_images);


// add the sum of final_bmp and bmp pixels to final_bmp's pixels
void add_sum(PixelMatrix bmp_matrix, PixelMatrix& final_bmp_matrix);


//  makes bitmap composite out of the bitmap vector passed in and returns it
void make_composite(vector<Bitmap> bitmap_images, PixelMatrix& final_bmp_matrix, int num_images);


// save the final_bmp to the filename in fname
void save(string fname, PixelMatrix final_bmp_matrix);


int main()

{
  vector<Bitmap> bitmap_images;
  Bitmap bmp;
  string text;
  PixelMatrix final_bmp_matrix;

  do
  {
    cout<<"Enter a .bmp file"<<endl;
    getline(cin,text);

    if (text=="DONE")
      cout<<bitmap_images.size()<<" images accepted"<<endl;
    else
    {
      bmp.open(text);
      if (bmp.isImage()==true)
      {
        bitmap_images.push_back(bmp);

        if (bitmap_images.size()==1)
        {
          PixelMatrix temp = bitmap_images[0].toPixelMatrix();
          final_bmp_matrix.resize(temp.size());
          for (int i=0;i<temp.size();i++)
            final_bmp_matrix[i].resize(temp[i].size());
        }
      }
    }
  } while (bitmap_images.size()<10 && text!="DONE");

  if(bitmap_images.size() ==10)
    cout<<"Limit 10 reached."<<endl;

  if (can_proceed(bitmap_images)==true)
  {
    make_composite(bitmap_images, final_bmp_matrix, bitmap_images.size());
    save("composite-aalneyadi.bmp", final_bmp_matrix);
  }

  return 0;
}

bool cmp_hw(PixelMatrix a, PixelMatrix b)
{
  if (a.size()!=b.size()) return false;
  
  for (int i=0;i<a.size();i++)
    if (a[i].size()!=b[i].size())
      return false;

  return true;
}

bool can_proceed(vector<Bitmap> bitmap_images)
{
  //to proceed we must have at least 2 images with the same width and height
  //dimensions
  
  if (bitmap_images.size() >= 2)
  {
    //check that the dimensions match the first one
    for (int i=0;i<bitmap_images.size();i++)
    {
      if (!cmp_hw(bitmap_images[0].toPixelMatrix(),bitmap_images[i].toPixelMatrix()))
      {
        cout<<"Invalid dimensions."<<endl;
        return false;
      }
      return true;
    }
  } else {
    cout<<"You must have at least 2 files to make a composite image."
      <<endl;
    return false;
  }
}

void add_sum(PixelMatrix bmp_matrix, PixelMatrix& final_bmp_matrix)
{
  for (int i=0;i<final_bmp_matrix.size();i++)
  {
    for(int j=0;j<final_bmp_matrix[i].size();j++)
    {
      final_bmp_matrix[i][j].red += bmp_matrix[i][j].red;
      final_bmp_matrix[i][j].green += bmp_matrix[i][j].green;
      final_bmp_matrix[i][j].blue += bmp_matrix[i][j].blue;
    }
  }
}

void make_composite(vector<Bitmap> bitmap_images, PixelMatrix& final_bmp_matrix, int num_images)
{
  for (int i=0;i<bitmap_images.size();i++)
  {
    add_sum(bitmap_images[i].toPixelMatrix(), final_bmp_matrix);
    cout<<"Image "<<(i + 1)<<" of "<<num_images<<" done"<<endl;
  }

  for (int i=0;i<final_bmp_matrix.size();i++)
  {
    for (int j=0;j<final_bmp_matrix[i].size();j++)
    {
      final_bmp_matrix[i][j].red /= num_images;
      final_bmp_matrix[i][j].green /= num_images;
      final_bmp_matrix[i][j].blue /= num_images;
    }
  }
}

void save(string fname, PixelMatrix final_bmp_matrix)
{
  Bitmap temp;
  temp.fromPixelMatrix(final_bmp_matrix);
  if (temp.isImage()==true)
  {
    temp.save(fname);
    cout<<"\nFile successfuly saved as 'composite-aalneyadi.bmp'"<<endl;
  } else
    cout<<"It is not a valid bitmap!"<<endl;
}
