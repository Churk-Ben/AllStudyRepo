#pragma once

#include "locenv.hpp"
typedef std::vector<std::pair<int,int>> ans;

// ==================== 你的解题逻辑 ====================
static bool can_connect(const Cell& a, const Cell& b) {
    return (a.color() == b.color() || a.color() == 0 || b.color() == 0);
}

bool is_neig(std::pair<int,int> a, std::pair<int,int> b)
{
    if((abs(a.first - b.first) + abs(a.second - b.second)) >= 2){return false;}
    else {return true;}
}

void DFS(int r,int c,const Board& board,
    std::vector<std::pair<int,int>>& route, int colorlock)
{
    if(!route.empty() && !is_neig(std::make_pair(r,c),route.back())){return;}
    route.emplace_back(r,c);
    for(int i = 0;i < 4;i++)
    {
        int nr = r + DR[i];
        int nc = c + DC[i];

        if (!board.in_bounds(nr, nc)){continue;}//越界检查
        if (std::find(route.begin(), route.end(),std::make_pair(nr, nc)) != route.end()){continue;}//重复检查

        if ((board.at(nr,nc).color() == colorlock || board.at(nr,nc).color() == 0) && can_connect(board.at(r,c), board.at(nr,nc))) {
            DFS(nr, nc, board, route, colorlock);   // 递归探索，不提前返回
        }
    }
}

void best_path_elem(std::vector<std::pair<std::vector<std::pair<int,int>>,int>> &rouPlen,const Board &board,int N){
    for (int r = 0; r < N; ++r) 
    {
        for (int c = 0; c < N; ++c) 
        {
            std::vector<std::pair<int,int>> route;
            double score = 0;
            int cnt=0;
            int extra =0;
            DFS(r,c,board,route,board.at(r,c).color());//获取可行的路径
            if(route.size() < 2){continue;}
            for(auto i : route)//获取路径可消除的块数
            {
                score=score+sqrt(i.first+1)*0.3+1;
                ++cnt;
                if(board.at(i.first,i.second).is_bomb())
                {
                    for(int j = 0; j < 8; j++)
                    {
                        int canr = i.first + DR8[j];
                        int canc = i.second + DC8[j];
                        if(find(route.begin(),route.end(),std::make_pair(canr,canc)) != route.end()
                            || canr < 0 || canr >= N || canc < 0 || canc >= N){continue;}
                        else{
                            extra++;
                        }
                    }
                }
            }
            score+=10*cnt+floor(18.0*(sqrt(cnt)-1)*(sqrt(cnt)-1))+10*extra;
            rouPlen.emplace_back(route,score);
        }
    }
}

void dfs(const Board& board, int r, int c, int target_color,
         std::vector<std::pair<int, int>>& current_path,
         std::vector<std::vector<bool>>& visited,
         std::vector<std::vector<std::pair<int, int>>>& all_paths) {
    
    current_path.emplace_back(r, c);
    visited[r][c] = true;

    if (current_path.size() >= 2) {
        all_paths.push_back(current_path);
    }

    int max_path_length = 30;
    if (current_path.size() < max_path_length) {
        for (int d = 0; d < 4; ++d) {
            int nr = r + DR[d];
            int nc = c + DC[d];
            if (board.in_bounds(nr, nc) && !visited[nr][nc]) {
                int cell_color = board.at(nr, nc).color();
                if (cell_color == target_color || cell_color == 0 || target_color == 0) {
                    int new_target = (target_color != 0) ? target_color : cell_color;
                    dfs(board, nr, nc, new_target, current_path, visited, all_paths);
                }
            }
        }
    }

    current_path.pop_back();
    visited[r][c] = false;
}

std::vector<std::vector<std::pair<int, int>>> find_all_paths(const Board& board) {
    std::vector<std::vector<std::pair<int, int>>> all_paths;
    int N = board.N;
    
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            std::vector<std::pair<int, int>> current_path;
            std::vector<std::vector<bool>> visited(N, std::vector<bool>(N, false));
            int target_color = board.at(r, c).color();
            dfs(board, r, c, target_color, current_path, visited, all_paths);
        }
    }

    std::sort(all_paths.begin(), all_paths.end(), [&board](const auto& a, const auto& b) {
        int score_a = path_score(board, a);
        int score_b = path_score(board, b);
        if (score_a != score_b) {
            return score_a > score_b;
        }
        return a.size() > b.size();
    });

    if (all_paths.size() > 500) {
        all_paths.resize(500);
    }

    return all_paths;
}

ans find_best_path(const Board &board) {
    int N = board.N;
    
    auto all_paths = find_all_paths(board);
    
    if (all_paths.empty()) {
        return {{0, 0}, {0, 1}};
    }

    int best_total = -1;
    std::vector<std::pair<int, int>> best_path;

    int sample_size = std::min(20, (int)all_paths.size());
    for (int i = 0; i < sample_size; ++i) {
        const auto& path = all_paths[i];
        int score1 = path_score(board, path);
        Board board1 = board.preview(path);
        
        if (board1.is_deadlocked()) {
            continue;
        }

        auto paths2 = find_all_paths(board1);
        if (paths2.empty()) continue;
        int score2 = path_score(board1, paths2[0]);
        Board board2 = board1.preview(paths2[0]);
        
        if (board2.is_deadlocked()) {
            int total = score1 + score2;
            if (total > best_total) { best_total = total; best_path = path; }
            continue;
        }
        
        auto paths3 = find_all_paths(board2);
        if (paths3.empty()) {
            int total = score1 + score2;
            if (total > best_total) { best_total = total; best_path = path; }
            continue;
        }
        int score3 = path_score(board2, paths3[0]);
        Board board3 = board2.preview(paths3[0]);
        
        if (board3.is_deadlocked()) {
            int total = score1 + score2 + score3;
            if (total > best_total) { best_total = total; best_path = path; }
            continue;
        }
        
        auto paths4 = find_all_paths(board3);
        int score4 = 0;
        if (!paths4.empty()) {
            score4 = path_score(board3, paths4[0]);
        }

        int total = score1 + score2 + score3 + score4;
        if (total > best_total) {
            best_total = total;
            best_path = path;
        }
    }

    if (!best_path.empty()) {
        return best_path;
    }

    return all_paths[0];
}

