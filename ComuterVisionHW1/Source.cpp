#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

using namespace std;
using namespace cv;

bool startDrawing = false;
int startX;
int startY;
int endX;
int endY;
int maxWidth;
int maxHeight;

void fixSize();
void MouseCallBackFunc(int event, int x, int y, int flags, void* sourceImg);

int main()
{
	// Read image from file 
	Mat sourceImg = imread("Zakynthos.jpg");

	// If fail to read the image
	if (sourceImg.empty())
	{
		cout << "Error loading the image" << endl;
		return -1;
	}

	// Set max size
	maxWidth = sourceImg.cols;
	maxHeight = sourceImg.rows;

	// Create a window
	namedWindow("Source Image", CV_WINDOW_AUTOSIZE);

	// Set the callback function for any mouse event
	setMouseCallback("Source Image", MouseCallBackFunc, &sourceImg);

	// Show the image
	imshow("Source Image", sourceImg);

	// Wait until user press some key
	waitKey(0);

	return 0;

} // End main


void MouseCallBackFunc(int event, int x, int y, int flags, void* sourceImg)
{
	waitKey(15);
	if (event == EVENT_LBUTTONDOWN)
	{
		startDrawing = true;
		startX = x;
		startY = y;
	}

	else if (event == EVENT_LBUTTONUP)
	{
		startDrawing = false;

		if (endX == 0 || endY == 0) {
			endX = x;
			endY = y;
		}

		fixSize();

		Rect croppedrectangle = Rect(startX, startY, (endX - startX), (endY - startY));

		Mat img = imread("Zakynthos.jpg");
		Mat croppedImg = img(croppedrectangle);

		// Destroy the exist window and Create a new one
		cvDestroyWindow("Selected Image");
		namedWindow("Selected Image", CV_WINDOW_AUTOSIZE);

		// Show the image
		imshow("Selected Image", croppedImg);
	}

	// Drawing rectangle
	else if (event == EVENT_MOUSEMOVE)
	{
		if (startDrawing) {

			endX = x > maxWidth ? maxWidth - 2 : x;
			endY = y > maxHeight ? maxHeight - 2 : y;

			if (endX < 0)
				endX = 0;

			if (endY < 0)
				endY = 0;

			Mat img = imread("Zakynthos.jpg");

			// Drawing rectangle on img
			rectangle(img, CvPoint(startX, startY), CvPoint(endX, endY), Scalar(0, 0, 255), 2);

			// Show the image with rectangle
			imshow("Source Image", img);
		}
	}
}

void fixSize() {

	if (endX < 0)
		endX = 0;

	if (endY < 0)
		endY = 0;

	endX = endX > maxWidth ? maxWidth : endX;
	endY = endY > maxHeight ? maxHeight : endY;

	if (startX >= endX) {
		swap(startX, endX);

		if (startX == endX)
			--startX;
	}

	if (startY >= endY) {
		swap(startY, endY);

		if (startY == endY)
			--startY;
	}
}
