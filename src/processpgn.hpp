#ifndef PROCESSPGN_HPP_INCLUDED
#define PROCESSPGN_HPP_INCLUDED

#include <string_view>

namespace LichessBot {

void process_pgn(const std::string& inputfile, const std::string& outputfile);

}

#endif
