#include "OpenPoseVideo.h"

using namespace std;
using namespace cv;
using namespace cv::dnn;

namespace computervision
{
#define MPI

#ifdef MPI
	const int POSE_PAIRS[7][2] =
	{
		{0,1}, {1,2}, {2,3},
		{3,4}, {1,5}, {5,6},
		{6,7}
	};

	string protoFile = "res/pose/mpi/pose_deploy_linevec_faster_4_stages.prototxt";
	string weightsFile = "res/pose/mpi/pose_iter_160000.caffemodel";

	int nPoints = 8;
#endif

#ifdef COCO
	const int POSE_PAIRS[17][2] =
	{
		{1,2}, {1,5}, {2,3},
		{3,4}, {5,6}, {6,7},
		{1,8}, {8,9}, {9,10},
		{1,11}, {11,12}, {12,13},
		{1,0}, {0,14},
		{14,16}, {0,15}, {15,17}
	};

	string protoFile = "pose/coco/pose_deploy_linevec.prototxt";
	string weightsFile = "pose/coco/pose_iter_440000.caffemodel";

	int nPoints = 18;
#endif
	Net net;

	void OpenPoseVideo::setup() {
		net = readNetFromCaffe(protoFile, weightsFile);
	}

	void OpenPoseVideo::movementSkeleton(Mat inputImage, std::function<void(std::vector<Point>,cv::Mat poinst_on_image)> f) {
		std::cout << "movement skeleton start" << std::endl;

		int inWidth = 368;
		int inHeight = 368;
		float thresh = 0.01;

		Mat frame;
		int frameWidth = inputImage.size().width;
		int frameHeight = inputImage.size().height;

		double t = (double)cv::getTickCount();
		std::cout << "reading input image and blob" << std::endl;

		frame = inputImage;
		Mat inpBlob = blobFromImage(frame, 1.0 / 255, Size(inWidth, inHeight), Scalar(0, 0, 0), false, false);

		std::cout << "done reading image and blob" << std::endl;

		net.setInput(inpBlob);

		std::cout << "done setting input to net" << std::endl;
		Mat output = net.forward();

		int H = output.size[2];
		int W = output.size[3];

		std::cout << "about to find position of boxy parts" << std::endl;
		// find the position of the body parts
		vector<Point> points(nPoints);
		for (int n = 0; n < nPoints; n++)
		{
			// Probability map of corresponding body's part.
			Mat probMap(H, W, CV_32F, output.ptr(0, n));

			Point2f p(-1, -1);
			Point maxLoc;
			double prob;
			minMaxLoc(probMap, 0, &prob, 0, &maxLoc);
			if (prob > thresh)
			{
				p = maxLoc;
				p.x *= (float)frameWidth / W;
				p.y *= (float)frameHeight / H;

				circle(frame, cv::Point((int)p.x, (int)p.y), 8, Scalar(0, 255, 255), -1);
				cv::putText(frame, cv::format("%d", n), cv::Point((int)p.x, (int)p.y), cv::FONT_HERSHEY_COMPLEX, 1.1, cv::Scalar(0, 0, 255), 2);
			}
			points[n] = p;
		}

		cv::putText(frame, cv::format("time taken = %.2f sec", t), cv::Point(50, 50), cv::FONT_HERSHEY_COMPLEX, .8, cv::Scalar(255, 50, 0), 2);
		std::cout << "time taken: " << t << std::endl;
		//imshow("Output-Keypoints", frame);
		//imshow("Output-Skeleton", frame);
		std::cout << "about to call points receiving method" << std::endl;
		f(points,frame);
	}
}