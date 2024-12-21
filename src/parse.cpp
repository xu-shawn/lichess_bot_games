#include "parse.hpp"

namespace LichessBot {

PGNFilter::PGNFilter(std::ofstream&& fout) :
    processed_games_(0),
    moveCount_{0},
    buffer_{},
    file_out_{std::move(fout)} {}

void PGNFilter::startPgn() {
    if (processed_games_ % 100 == 0)
        std::cout << processed_games_ << " games processed" << std::endl;
    buffer_.str(std::string());
}

void PGNFilter::header(std::string_view key, std::string_view value) {
    buffer_ << "[" << key << " " << std::quoted(value) << "]\n";
    if (key == "Result")
        result_ = value;
}

void PGNFilter::startMoves() {
    moveCount_ = 0;
    buffer_ << "\n";
}

void PGNFilter::move(std::string_view move, std::string_view comment) {
    if (moveCount_ % 2 == 0)
    {
        buffer_ << moveCount_ / 2 + 1 << ". ";
    }
    buffer_ << move << " ";
    moveCount_++;
}

void PGNFilter::endPgn() {
    file_out_ << buffer_.str() << result_ << "\n\n";
    processed_games_++;
}

}
