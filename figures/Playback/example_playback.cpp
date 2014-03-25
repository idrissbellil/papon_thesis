#include <pcl/io/pcd_io.h>
#include <pcl/common/time.h>
#include <pcl/console/parse.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/pcl_base.h>

#include <pcl/tracking/tracking.h>

#include <boost/regex.hpp>
#include <boost/format.hpp>
#include <boost/filesystem.hpp>
#include <set>

#include "CColor.h"

using namespace pcl;
using namespace pcl::io;
using namespace pcl::console;

typedef pcl::PointXYZRGBL LabelPointT;
typedef pcl::PointCloud<LabelPointT> LabelCloudT;
typedef pcl::PointXYZRGB PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

bool show_original = true;
bool show_supervoxels = true;
bool show_models = false;
bool show_result = true;
bool show_tracks = true;
bool show_orientation = false;
bool show_particles = true;
bool show_coloredsv = false;
bool pause_playback = true;
bool clear_view = false;
bool showfulllabel = false;
bool showfullrgb = false;
bool controlCamera = true;
bool resetCamera = false;

void 
keyboard_callback (const pcl::visualization::KeyboardEvent& event, void*)
{
  if (event.getKeyCode () == '1')
    show_original = !show_original;
  if (event.getKeyCode () == '2')
    show_supervoxels = !show_supervoxels;
  if (event.getKeyCode () == '3')
    show_models = !show_models;
  if (event.getKeyCode () == '4')
    show_tracks = !show_tracks;
  if (event.getKeyCode () == '5')
    show_result = !show_result;
  if (event.getKeyCode () == '6')
    show_coloredsv = !show_coloredsv;
  if (event.getKeyCode () == '7')
    show_orientation = !show_orientation;
  if (event.getKeyCode () == '9')
    show_particles = !show_particles;
  if (event.getKeyCode () == '0')
    pause_playback = !pause_playback;
  if (event.getKeyCode () == '`')
    resetCamera = true;
  if (event.getKeyCode () == '8')
    controlCamera = !controlCamera;
}

int
main (int argc, char ** argv)
{
  if (argc < 2)
  {
    pcl::console::print_info ("\n \n Syntax is: %s {-1 <pcd-file-name-format>}\n" 
    "Format should be in standard wildcard format (e.g. \"*.pcd\") MUST HAVE QUOTES \n"
    "Program will iterate through sorted list of all pcd files matching this format"
    , argv[0]);
    return (1);
  }
  
  boost::shared_ptr <CColor>  pColors(new CColor(1000)); 
  colorRGB clr;
  
  bool pcd_file_specified = pcl::console::find_switch (argc, argv, "-1");
  std::string pcd_path_string1;
  if (!pcd_file_specified)
  {
    cout << "No cloud specified!\n";
    return (1);
  }else
  {
    pcl::console::parse (argc,argv,"-1",pcd_path_string1);
  }
   
  namespace fs = boost::filesystem;
  cout<< "Loading pointcloud, using format "<< pcd_path_string1<< std::endl;
  fs::path pcd_path1(pcd_path_string1);
  
  std::set<boost::filesystem::path> input_files_model;
  std::set<boost::filesystem::path> input_files_original;
  std::set<boost::filesystem::path> input_files_supervoxels;
  std::set<boost::filesystem::path> input_files_track;
  std::set<boost::filesystem::path> input_files_particles;
  std::set<boost::filesystem::path> input_files_orientation;
  std::set<boost::filesystem::path> input_files_result;
  std::set<boost::filesystem::path> input_files_coloredsv;
  std::set<boost::filesystem::path> input_files_fullrgbl;
  
  cout << "Directory containing cloud files=" << pcd_path1.parent_path ()<<"\n";
  cout << "Filename match string 1=" << pcd_path1.filename ()<<"\n";
  
  std::string wildcard_string_base = pcd_path1.filename (). string ();
  boost::replace_all(wildcard_string_base, "*", ".*");
  std::string wildcard_string_model = ".*labeled_" + wildcard_string_base + "$";
  std::string wildcard_string_original = ".*combined_ds_" + wildcard_string_base + "$";
  std::string wildcard_string_supervoxels = ".*supervoxels_" + wildcard_string_base + "$";
  std::string wildcard_string_track = ".*track_" + wildcard_string_base + "$";
  std::string wildcard_string_orientation = ".*orientation_" + wildcard_string_base + "$";
  std::string wildcard_string_coloredsv = ".*coloredsv_" + wildcard_string_base + "$";
  std::string wildcard_string_result = ".*result_" + wildcard_string_base + "$";
  std::string wildcard_string_particles = ".*particles_" + wildcard_string_base + "$";

  std::string wildcard_string_fullrgbl = "./0.*.pcd$";
  
  if (fs::exists (pcd_path1.parent_path ()) && fs::is_directory (pcd_path1.parent_path () ))
  {
    boost::regex pattern_model(wildcard_string_model);
    boost::regex pattern_original(wildcard_string_original);


    
    fs::directory_iterator end_iter;
    for( fs::directory_iterator dir_iter(pcd_path1.parent_path ()) ; dir_iter != end_iter ; ++dir_iter)
    {
      //std::cout << "Attempting to match "<<dir_iter->path ().string ()<<"\n";
      if (fs::is_regular_file(dir_iter->status()) )
      {
        std::cout << dir_iter->path ().string () << "\n";
        if (boost::regex_match (dir_iter->path ().string (), pattern_model))
        {
          input_files_model.insert( *dir_iter );
          cout << "Adding "<<dir_iter->path ().string ()<<" to models\n";
        }
        else if (boost::regex_match (dir_iter->path ().string (), pattern_original))
        {
          input_files_original.insert( *dir_iter );
          cout << "Adding "<<dir_iter->path ().string ()<<" to original\n";
        }
      }
    }
  }
  else
  {
    cout << "Wildcard string original="<<wildcard_string_original<<endl;
    cout << pcd_path1 << " does not exist\n";
    return (1);
  }
  cout << "Found "<<input_files_model.size() << " files matching "<<wildcard_string_model<<"\n";
  cout << "Found "<<input_files_original.size() << " files matching "<<wildcard_string_original<<"\n";
  cout << "Found "<<input_files_supervoxels.size() << " files matching "<<wildcard_string_supervoxels<<"\n";
  cout << "Found "<<input_files_track.size() << " files matching "<<wildcard_string_track<<"\n";
  cout << "Found "<<input_files_orientation.size() << " files matching "<<wildcard_string_orientation<<"\n";
  cout << "Found "<<input_files_coloredsv.size() << " files matching "<<wildcard_string_coloredsv<<"\n";
  cout << "Found "<<input_files_result.size() << " files matching "<<wildcard_string_result<<"\n";
  cout << "Found "<<input_files_fullrgbl.size() << " files matching "<<wildcard_string_fullrgbl<<"\n";

  
  
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
  viewer->setBackgroundColor (0, 0, 0);
  viewer->registerKeyboardCallback(keyboard_callback, 0);
  
  
  pcl::PointCloud<PointXYZRGB>::Ptr original ( new pcl::PointCloud<PointXYZRGB> );
  LabelCloudT::Ptr model ( new LabelCloudT );
  pcl::PointCloud<PointXYZRGB>::Ptr model_copy ( new pcl::PointCloud<PointXYZRGB> );


  std::set<fs::path>::iterator file_itr_original = input_files_original.begin ();
  std::set<fs::path>::iterator file_itr_model = input_files_model.begin ();

  //std::set<fs::path>::iterator file_itr_fullrgbl = input_files_fullrgbl.begin ();

  bool added_this_frame = false;

  StopWatch timer;

  int num_frames = 1;

 
  
  for ( ;file_itr_original != input_files_original.end (); )
  {
    

      
    double t_start = timer.getTime ();
    if (!pause_playback)
      cout << "----------------------Starting new frame ("<<num_frames<<") ------------------\n";
      
  
    if (show_original)
    {
      loadPCDFile (file_itr_original->native (), *original);
      pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> orig(original);

      if (!viewer->updatePointCloud (original, orig, "original"))
        viewer->addPointCloud (original, orig, "original");
      viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE,2.0, "original");
    }else
    {
      viewer->removePointCloud ("original");
    }
   
        
    if (show_models)
    {
      loadPCDFile (file_itr_model->native (), *model);
      copyPointCloud (*model, *model_copy);
      PointCloudT::iterator copy_itr = model_copy->begin ();
      for (LabelCloudT::iterator itr = model->begin (); itr != model->end (); ++itr, ++copy_itr)
      {
        pColors->GetColor(itr->label, clr);
        copy_itr->r = clr.m_R;
        copy_itr->g = clr.m_G;
        copy_itr->b = clr.m_B;   
      }
      if (!viewer->updatePointCloud (model_copy,  "model"))
        viewer->addPointCloud (model_copy, "model");
      viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE,4.0, "model");
    }
    else
    {
      viewer->removePointCloud ("model");
    }
    
    
    if (resetCamera)
    {
      resetCamera = false;
      viewer->setCameraPosition(-1.5, -0.30,-0.52, -0.107422, 0.0322207, 0.667592, 0.430291, -0.866065, -0.254521);
      num_frames = 0;
    }
    if (!controlCamera)
    {
      double angle = num_frames / 90.0;
      double zval = 1.5;
      double xval = 0.25 + 2 * sin (angle);
      double yval =  0.75 + (1.75 * cos (angle));
      viewer->setCameraPosition(xval, yval, zval, 0, 0.5, 0, 0, 0, 1);
    }else if (!pause_playback)
    {
      num_frames--;
    }
    

    viewer->spinOnce (1, true);
    double t_spent = timer.getTime () - t_start; 
    int sleep_ms = ((100 - t_spent) > 0) ? (100 - t_spent) : 0;
    boost::this_thread::sleep (boost::posix_time::milliseconds (sleep_ms));
    if (!pause_playback)
    {
      ++file_itr_original; ++file_itr_model; 
      num_frames++;
    }
    std::cout << "Framerate = "<< 1000.0 / (timer.getTime () - t_start) << "fps\n";
  }
  while (!viewer->wasStopped ())
  {
    double t_start = timer.getTime ();
    
    
    if (show_original)
    {
      pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> orig(original);
      if (!viewer->updatePointCloud (original, orig, "original"))
        viewer->addPointCloud (original, orig, "original");
      viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE,2.0, "original");
    }else
    {
      viewer->removePointCloud ("original");
    }
    
    
    if (show_models)
    {
      if (!viewer->updatePointCloud (model_copy,  "model"))
        viewer->addPointCloud (model_copy, "model");
      viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE,4.0, "model");
    }
    else
    {
      viewer->removePointCloud ("model");
    }
    
    if (resetCamera)
    {
      resetCamera = false;
      viewer->setCameraPosition(0.25, 2.5, 1.5, 0, 0.5, 0, 0, 0, 1);
      num_frames = 0;
    }
    if (!controlCamera)
    {
      double angle = num_frames / 90.0;
      double zval = 1.0;
      double xval = 0.25 + 2 * sin (angle);
      double yval =  0.75 + (1.75 * cos (angle));
      viewer->setCameraPosition(xval, yval, zval, 0, 0.5, 0, 0, 0, 1);
    }
    num_frames++;
    viewer->spinOnce (1, true);
    double t_spent = timer.getTime () - t_start; 
    int sleep_ms = ((100 - t_spent) > 0) ? (100 - t_spent) : 0;
    boost::this_thread::sleep (boost::posix_time::milliseconds (sleep_ms));
    //boost::this_thread::sleep (boost::posix_time::microseconds (1000));
  }
  return (0);
}