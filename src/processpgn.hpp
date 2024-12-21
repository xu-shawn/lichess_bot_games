#ifndef PROCESSPGN_HPP_INCLUDED
#define PROCESSPGN_HPP_INCLUDED

#include <string_view>

namespace LichessBot {

void process_pgn(std::string_view inputfile, std::string_view outputfile);

}

#endif
