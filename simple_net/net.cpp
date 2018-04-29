#define CPU_ONLY
#include <caffe/caffe.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>


int main(int argc, char** argv)
{
  caffe::Caffe::set_mode(caffe::Caffe::CPU);
  std::unique_ptr<caffe::Net<float> > net_;
  net_.reset(new caffe::Net<float>(argv[1], caffe::TEST));
  net_->CopyTrainedLayersFrom(argv[2]);
  cv::Mat img = cv::imread(argv[3], -1);
  cv::Mat img_fl;
  std::vector<cv::Mat> input_channels;
  //Show param
  std::cout << "Parameters of the net " << std::endl;
  std::cout << "number inputs " << net_->num_inputs() << std::endl;
  std::cout << "number outputs " << net_->num_outputs() << std::endl;
  caffe::Blob<float>* output_layer = net_->output_blobs()[0];
  std::cout << "output channel " << output_layer->channels() << std::endl;
  std::cout << "output height " << output_layer->height() << std::endl;
  std::cout << "output width " << output_layer->width() << std::endl;
  caffe::Blob<float>* input_layer = net_->input_blobs()[0];
  std::cout << "input channel " << input_layer->channels() << std::endl;
  std::cout << "input height " << input_layer->width() << std::endl;
  std::cout << "input width " << input_layer->width() << std::endl;

  //Prepare data to forward
  int width = input_layer->width();
  int height = input_layer->height();
  float* input_data = input_layer->mutable_cpu_data();
  for (size_t i = 0; i < input_layer->channels(); ++i)
  {
    cv::Mat channel(height, width, CV_32FC1, input_data);
    input_channels.push_back(channel);
    input_data += width * height;
  }
  img.convertTo(img_fl, CV_32FC3);
  cv::split(img_fl, input_channels);

  //Start forward
  net_->Forward();
  const float* begin = output_layer->cpu_data();
  const float* end = begin + output_layer->channels();
  std::vector<float> prob(begin, end);
  for(size_t i = 0; i < prob.size();i++)
    std::cout << prob[i] << " ";
    std::cout << " " << std::endl;
  return 0;
}
