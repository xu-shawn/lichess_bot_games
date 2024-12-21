#include "parse.hpp"

namespace LichessBot {

PGNFilter::PGNFilter(std::ofstream&& fout) :
    processed_games(0),
    moveCount{0},
    buffer{},
    file_out{std::move(fout)} {}

void PGNFilter::startPgn() {
    if (processed_games % 100 == 0)
        std::cout << processed_games << " games processed" << std::endl;
    buffer.clear();
}

void PGNFilter::header(std::string_view key, std::string_view value) {
    buffer << "[" << key << " " << std::quoted(value) << "]\n";
}

void PGNFilter::startMoves() {
    moveCount = 0;
    buffer << "\n";
}

void PGNFilter::move(std::string_view move, std::string_view comment) {
    if (moveCount % 2 == 0)
    {
        buffer << moveCount / 2 << ". ";
    }
    buffer << move << " ";
    moveCount++;
}

void PGNFilter::endPgn() {
    file_out << buffer.str();
    processed_games++;
}

}
