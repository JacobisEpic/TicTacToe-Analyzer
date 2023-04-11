// Copyright 2022 Jacob Chin jacobc@bu.edu
// Copyright 2022 Emika Hammond eth@bu.edu
// EC327 HW2 Q1

#include <iostream>
#include <string>
#include <vector>
#include "movedef.h"
char tttresult(std::string tttboard) {
  int cx = 0, co = 0, ct = 0, xc = 0, oc = 0;
  for (int a = 0; (a = tttboard.find('x', a)) != std::string::npos; a++) cx++;
  for (int b = 0; (b = tttboard.find('o', b)) != std::string::npos; b++) co++;
  for (int c = 0; (c = tttboard.find('#', c)) != std::string::npos; c++) ct++;
  if ((cx + co + ct) != 9 || (tttboard.length()) != 9) return 'e';
  std::vector<std::vector<int>> w = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6},
    {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}
  };
  std::string nb;
  for (int i = 0 ; i < 8 ; i++) {
    for (int j = 0 ; j < 3 ; j++) nb.push_back(tttboard.at(w.at(i).at(j)));
    if ("xxx" == nb) xc++;
    if ("ooo" == nb) oc++;
    nb.clear();
  }
  if ((xc > 0 && oc > 0 && (xc + oc > 1)) || (xc > 0 && cx == co) || (oc > 0
      && cx != co) || ((cx - co > 1) || co > cx)) return 'i';
  if (xc > 0) return 'x';
  if (oc > 0) return 'o';
  if (cx + co != 9 && ct > 0) return 'c';
  return 't';
}

char tttresult(std::vector<Move> board) {
  std::string startboard = "#########";
  char last = 'o';
  for (int i = 0 ; i < board.size() ; i++) {
    if (board.size() > 9 || board.at(i).r > 2 || board.at(i).c > 2) return 'e';
    if (board.at(i).player == last || tttresult(startboard) != 'c') return 'i';
    last = board.at(i).player;
    startboard.at((board.at(i).r * 3) + board.at(i).c) = board.at(i).player;
    if (i == (board.size() - 1)) return tttresult(startboard);
  }
  return 'c';
}

std::vector<std::string> get_all_boards() {
  std::vector<std::string> boards;
  for (int j = 0; j < 19683; j++) {
    int num = j;
    std::string str = "";
    for (int i = 0 ; i < 9 ; i++) {
      int remainder = num % 3;
      num /= 3;
      str += std::to_string(remainder);
    }
    std::string temp = "", tempo = "#xo";
    for (auto e : str) temp += tempo.at(e - '0');
    boards.push_back(temp);
  }
  return boards;
}

void ttt_tally() {
  std::vector<std::string> board = get_all_boards();
  std::vector<char> x{'x', 'o', 't', 'i', 'c'};
  std::vector<int> cou{0, 0, 0, 0, 0};
  for (auto e : board) {
    for (int i = 0; i < 5; i++)
      if (tttresult(e) == x.at(i)) cou.at(i)++;
  }
  for (int j = 0; j < 5; j++) std::cout << x.at(j) << ' ' << cou.at(j) << "\n";
}
// MAIN