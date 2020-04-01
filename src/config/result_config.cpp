#include "config/result_config.hpp"
#include "util/util.hpp"
#include "util/debug.hpp"
#include <set>

namespace MM {

std::string ResultConfig::to_string() const {
  std::stringstream ss;
  ss << "Output file: " << file << "\n";
  ss << "Output fields: ";
  if (output_config.write_ogeom)
    ss << " ogeom ";
  if (output_config.write_opath)
    ss << " opath ";
  if (output_config.write_pgeom)
    ss << " pgeom ";
  if (output_config.write_offset)
    ss << " offset ";
  if (output_config.write_error)
    ss << " error ";
  if (output_config.write_spdist)
    ss << " spdist ";
  if (output_config.write_cpath)
    ss << " cpath ";
  if (output_config.write_tpath)
    ss << " tpath ";
  if (output_config.write_mgeom)
    ss << " mgeom ";
  if (output_config.write_ep)
    ss << " ep ";
  if (output_config.write_tp)
    ss << " tp ";
  if (output_config.write_length)
    ss << " length ";
  return ss.str();
};

ResultConfig ResultConfig::load_from_xml(
    const boost::property_tree::ptree &xml_data) {
  ResultConfig config;
  config.file = xml_data.get<std::string>("fmm_config.output.file");
  if (xml_data.get_child_optional("fmm_config.output.fields")) {
    // Fields specified
    // close the default output fields (cpath,mgeom are true by default)
    config.output_config.write_cpath = false;
    config.output_config.write_mgeom = false;
    if (xml_data.get_child_optional("fmm_config.output.fields.ogeom")) {
      config.output_config.write_ogeom = true;
    }
    if (xml_data.get_child_optional("fmm_config.output.fields.opath")) {
      config.output_config.write_opath = true;
    }
    if (xml_data.get_child_optional("fmm_config.output.fields.cpath")) {
      config.output_config.write_cpath = true;
    }
    if (xml_data.get_child_optional("fmm_config.output.fields.tpath")) {
      config.output_config.write_tpath = true;
    }
    if (xml_data.get_child_optional("fmm_config.output.fields.mgeom")) {
      config.output_config.write_mgeom = true;
    }
    if (xml_data.get_child_optional("fmm_config.output.fields.pgeom")) {
      config.output_config.write_pgeom = true;
    }
    if (xml_data.get_child_optional("fmm_config.output.fields.offset")) {
      config.output_config.write_offset = true;
    }
    if (xml_data.get_child_optional("fmm_config.output.fields.error")) {
      config.output_config.write_error = true;
    }
    if (xml_data.get_child_optional("fmm_config.output.fields.spdist")) {
      config.output_config.write_spdist = true;
    }
    if (xml_data.get_child_optional("fmm_config.output.fields.ep")) {
      config.output_config.write_ep = true;
    }
    if (xml_data.get_child_optional("fmm_config.output.fields.tp")) {
      config.output_config.write_tp = true;
    }
    if (xml_data.get_child_optional("fmm_config.output.fields.length")) {
      config.output_config.write_length = true;
    }
    if (xml_data.get_child_optional("fmm_config.output.fields.all")) {
      config.output_config.write_ogeom = true;
      config.output_config.write_opath = true;
      config.output_config.write_pgeom = true;
      config.output_config.write_offset = true;
      config.output_config.write_error = true;
      config.output_config.write_spdist = true;
      config.output_config.write_cpath = true;
      config.output_config.write_mgeom = true;
      config.output_config.write_tpath = true;
      config.output_config.write_ep = true;
      config.output_config.write_tp = true;
      config.output_config.write_length = true;
    }
  }
  return config;
};

ResultConfig ResultConfig::load_from_arg(
    const cxxopts::ParseResult &arg_data) {
  ResultConfig config;
  config.file = arg_data["output"].as<std::string>();
  if (arg_data.count("output_fields") > 0) {
    config.output_config.write_cpath = false;
    config.output_config.write_mgeom = false;
    std::string fields = arg_data["output_fields"].as<std::string>();
    std::set<std::string> dict = string2set(fields);
    if (dict.find("opath") != dict.end()) {
      config.output_config.write_opath = true;
    }
    if (dict.find("cpath") != dict.end()) {
      config.output_config.write_cpath = true;
    }
    if (dict.find("mgeom") != dict.end()) {
      config.output_config.write_mgeom = true;
    }
    if (dict.find("ogeom") != dict.end()) {
      config.output_config.write_ogeom = true;
    }
    if (dict.find("tpath") != dict.end()) {
      config.output_config.write_tpath = true;
    }
    if (dict.find("pgeom") != dict.end()) {
      config.output_config.write_pgeom = true;
    }
    if (dict.find("offset") != dict.end()) {
      config.output_config.write_offset = true;
    }
    if (dict.find("error") != dict.end()) {
      config.output_config.write_error = true;
    }
    if (dict.find("spdist") != dict.end()) {
      config.output_config.write_spdist = true;
    }
    if (dict.find("ep") != dict.end()) {
      config.output_config.write_ep = true;
    }
    if (dict.find("tp") != dict.end()) {
      config.output_config.write_tp = true;
    }
    if (dict.find("length") != dict.end()) {
      config.output_config.write_length = true;
    }
    if (dict.find("all") != dict.end()) {
      config.output_config.write_ogeom = true;
      config.output_config.write_opath = true;
      config.output_config.write_pgeom = true;
      config.output_config.write_offset = true;
      config.output_config.write_error = true;
      config.output_config.write_spdist = true;
      config.output_config.write_cpath = true;
      config.output_config.write_mgeom = true;
      config.output_config.write_tpath = true;
      config.output_config.write_ep = true;
      config.output_config.write_tp = true;
      config.output_config.write_length = true;
    }
  }
  return config;
};

std::set<std::string> ResultConfig::string2set(
    const std::string &s) {
  char delim = ',';
  std::set<std::string> result;
  std::stringstream ss(s);
  std::string intermediate;
  while (getline(ss, intermediate, delim)) {
    result.insert(intermediate);
  }
  return result;
}
bool ResultConfig::validate() const {
  if (UTIL::file_exists(file))
  {
    SPDLOG_WARN("Overwrite existing result file {}",file);
  };
  std::string output_folder = UTIL::get_file_directory(file);
  if (!UTIL::folder_exist(output_folder)) {
    SPDLOG_CRITICAL("Output folder {} not exists",output_folder);
    return false;
  }
  return true;
};

}
