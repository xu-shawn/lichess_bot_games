#ifndef PARSE_HPP_INCLUDED
#define PARSE_HPP_INCLUDED

#include <fstream>
#include <iomanip>

#include "chess.hpp"

namespace LichessBot {

class PGNFilter: public chess::pgn::Visitor {
   public:
    PGNFilter(std::ofstream&& fout);
    virtual ~PGNFilter() = default;
    virtual void startPgn();
    virtual void header(std::string_view key, std::string_view value);
    virtual void startMoves();
    virtual void move(std::string_view move, std::string_view comment);
    virtual void endPgn();

   private:
    std::size_t       processed_games_;
    std::size_t       moveCount_;
    std::stringstream buffer_;
    std::string       result_;
    std::ofstream     file_out_;
};

}

#endif
