#include "processpgn.hpp"

#include <fstream>
#include <memory>
#include <string_view>

#include "chess.hpp"
#include "parse.hpp"

namespace LichessBot {

void process_pgn(const std::string& inputfile, const std::string& outputfile) {
    std::ifstream                        file{inputfile};
    std::unique_ptr<chess::pgn::Visitor> pgn_parser =
      std::make_unique<PGNFilter>(std::ofstream{outputfile});
    chess::pgn::StreamParser parser{file};

    parser.readGames(*pgn_parser);
}

}
