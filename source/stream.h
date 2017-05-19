#pragma once

#include <cassert>
#include <codecvt>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/locale.hpp>

#include "transform.h"
#include "unconstructable.h"

namespace braid {
  using path_vector = std::vector<boost::filesystem::path>;

  namespace stream {
    namespace file {
      template<typename CharT = char, typename Traits = std::char_traits<CharT>>
      inline std::basic_string<CharT, Traits> read(const boost::filesystem::path& path) {
        boost::filesystem::basic_ifstream<CharT, Traits> buf(path, std::ios_base::in);

        return boost::locale::conv::from_utf<CharT>(transform::stream_to_string(buf));
      }

      template<>
      inline std::basic_string<char, std::char_traits<char>> read<char, std::char_traits<char>>(const boost::filesystem::path& path) {
        boost::filesystem::basic_ifstream<char, std::char_traits<char>> buf(path, std::ios_base::in);

        return transform::stream_to_string(buf);
      }

      template<typename CharT = char, typename Traits = std::char_traits<CharT>>
      inline void write(const boost::filesystem::path& path, const std::basic_string<CharT, Traits>& string) {
        boost::filesystem::ofstream buf(path, std::ios_base::out);

        buf << boost::locale::conv::to_utf<char>(string);
      }

      template<>
      inline void write(const boost::filesystem::path& path, const std::basic_string<char, std::char_traits<char>>& string) {
        boost::filesystem::ofstream buf(path, std::ios_base::out);

        buf << string;
      }
    }
  }
}