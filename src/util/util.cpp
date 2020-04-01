/**
 * Content
 * Utility functions
 *
 * @author: Can Yang
 * @version: 2017.11.11
 */
#include "util/util.hpp"

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <chrono>
#include <vector>
#include <ctime>
#include "network/type.hpp"

namespace std {

std::ostream &operator<<(std::ostream &os, const MM::Traj_Candidates &tr_cs) {
  os << "\nCandidate "
     << std::fixed << std::setw(4) << "step" << ";"
     << std::fixed << std::setw(6) << "index" << ";"
     << std::fixed << std::setw(8) << "offset" << ";"
     << std::fixed << std::setw(8) << "distance" << ";"
     << std::fixed << std::setw(8) << "edge_id" << '\n';
  for (auto tr_cs_iter = tr_cs.begin();
       tr_cs_iter != tr_cs.end(); ++tr_cs_iter) {
    for (auto p_cs_iter = tr_cs_iter->begin();
         p_cs_iter != tr_cs_iter->end();
         ++p_cs_iter) {
      os << "Candidate "
         << std::fixed << std::setw(4) << std::distance(tr_cs.begin(),
             tr_cs_iter) << ";"
         << std::fixed << std::setw(6) << p_cs_iter->index << ";"
         << std::fixed << std::setw(8) << p_cs_iter->offset << ";"
         << std::fixed << std::setw(8) << p_cs_iter->dist << ";"
         << std::fixed << std::setw(8) << p_cs_iter->edge->id << '\n';
    }
  }
  return os;
}

std::ostream &operator<<(std::ostream &os, const MM::OptCandidatePath &opath) {
  for (int i = 0; i < opath.size(); ++i) {
    // std::cout <<"Write edge "<< i <<" edge "<< opath[i]->edge->id <<"\n";
    os << opath[i]->edge->id;
    if (i != opath.size() - 1)
      os << ",";
  }
  return os;
}

std::ostream &operator<<(std::ostream &os, const MM::Point &geom) {
  os << std::setprecision(12) << boost::geometry::wkt(geom);
  return os;
}

} // namespace std

namespace MM {

namespace UTIL {

double meter2degree(double dist_meter) {
  return dist_meter / 1.11321e+5;
}

/**
 * Check if the file exists or not
 */
bool file_exists(const char *filename) {
  struct stat buf;
  if (stat(filename, &buf) != -1) {
    return true;
  }
  return false;
}

bool file_exists(const std::string &filename) {
  return file_exists(filename.c_str());
}

bool string2bool(const std::string &str) {
  return str == "true" || str == "t" || str == "1";
}

/**
 *  Print the candidates of trajectory in a table with header of
 *  step;offset;distance;edge_id
 */
void print_traj_candidates(Traj_Candidates &tr_cs) {
  std::cout << "step;index;offset;distance;edge_id" << '\n';
  Traj_Candidates::iterator tr_cs_iter;
  Point_Candidates::iterator p_cs_iter;
  for (tr_cs_iter = tr_cs.begin(); tr_cs_iter != tr_cs.end(); ++tr_cs_iter) {
    for (p_cs_iter = tr_cs_iter->begin(); p_cs_iter != tr_cs_iter->end();
         ++p_cs_iter) {
      std::cout << std::distance(tr_cs.begin(), tr_cs_iter) << ";"
                << p_cs_iter->index << ";" << p_cs_iter->offset << ";"
                << p_cs_iter->dist << ";" << p_cs_iter->edge->id << '\n';
    }
  }
}

void print_traj_candidates_summary(Traj_Candidates &tr_cs) {
  std::cout << "point_idx;candidate_count" << '\n';
  Traj_Candidates::iterator tr_cs_iter;
  for (tr_cs_iter = tr_cs.begin(); tr_cs_iter != tr_cs.end(); ++tr_cs_iter) {
    std::cout << std::distance(tr_cs.begin(), tr_cs_iter) << ";"
              << tr_cs_iter->size() << '\n';
  }
}

/**
 * Print the number of candidates for each point of trajectory
 */
void print_traj_candidates_count(Traj_Candidates &tr_cs) {
  Traj_Candidates::iterator tr_cs_iter;
  std::cout << "Summary of transition graph: " << '\n';
  std::cout << "Count of candidates" << '\n';
  for (tr_cs_iter = tr_cs.begin(); tr_cs_iter != tr_cs.end(); ++tr_cs_iter) {
    std::cout << tr_cs_iter->size() << " ";
  }
  std::cout << '\n';
}

/**
 * Print the OGRLineString in WKT format
 */
void print_geometry(LineString &geom) {
  std::cout << geom.export_wkt() << '\n';
}

// Get current timestamp
std::chrono::time_point<std::chrono::system_clock> get_current_time() {
  return std::chrono::system_clock::now();
}

// Print a timestamp
void print_time(
    const std::chrono::time_point<std::chrono::system_clock> &start_time) {
  std::time_t start_time_t = std::chrono::system_clock::to_time_t(start_time);
  std::cout << "Time " << std::ctime(&start_time_t) << '\n';
}

/**
 * Calculate the duration between two timestamps in unit of seconds
 */
double get_duration(
    const std::chrono::time_point<std::chrono::system_clock> &start_time,
    const std::chrono::time_point<std::chrono::system_clock> &end_time) {
  std::chrono::duration<double> elapsed_seconds = end_time - start_time;
  return elapsed_seconds.count();
}
bool check_file_extension(const std::string &filename,
                          const std::string &extension_list_str) {
  bool result = false;
  std::stringstream ss;
  std::string fn_extension = filename.substr(
      filename.find_last_of('.') + 1);
  std::vector<std::string> extensions =
      string2vec<std::string>(extension_list_str);
  for(const auto &extension:extensions){
    if (fn_extension==extension)
      result = true;
  }
  return result;
}

bool folder_exist(const std::string &folder_name)
{
  if (folder_name.empty()) return true;
  struct stat sb;
  if (stat(folder_name.c_str(),&sb) == 0 && S_ISDIR(sb.st_mode)) {
    return true;
  }
  return false;
}

std::string get_file_directory(const std::string &fn){
  std::size_t found = fn.find_last_of("/");
  if (found!=std::string::npos){
    return fn.substr(0,found);
  }
  return {};
};

} // Util
} // MM
