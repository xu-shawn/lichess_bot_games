#include "parse.hpp"

namespace LichessBot {

PGNFilter::PGNFilter(std::ofstream&& fout) :
    bot_flag_{0},
    processed_games_(0),
    written_games_{0},
    moveCount_{0},
    buffer_{},
    file_out_{std::move(fout)} {}

void PGNFilter::startPgn() {
    if (processed_games_ % 10000 == 0)
        std::cout << processed_games_ << " games processed, " << written_games_ << " written"
                  << std::endl;
    buffer_.str(std::string());
    bot_flag_ = 0;
}

void PGNFilter::header(std::string_view key, std::string_view value) {
    buffer_ << "[" << key << " " << std::quoted(value) << "]\n";
    if (key == "Result")
        result_ = value;
    else if (key == "WhiteTitle")
        bot_flag_ += (value == "BOT");
    else if (key == "BlackTitle")
        bot_flag_ += (value == "BOT");
}

void PGNFilter::startMoves() {
    skipPgn(bot_flag_ != 1);
    moveCount_ = 0;
    buffer_ << "\n";
}

void PGNFilter::move(std::string_view move, std::string_view comment) {
    if (moveCount_ % 2 == 0)
        buffer_ << moveCount_ / 2 + 1 << ". ";
    buffer_ << move << " ";
    moveCount_++;
}

void PGNFilter::endPgn() {
    processed_games_++;
    if (bot_flag_ != 1)
        return;
    written_games_++;
    file_out_ << buffer_.str() << result_ << "\n\n";
}
}
