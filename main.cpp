#include <iostream>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <limits>

enum PointType {
    BeginTime,
    EndTime
};

struct timePoint {
    std::string UserName;
    PointType PT;
};

std::unordered_map<PointType, int> point_sign = {
    {PointType::BeginTime, -1},
    {PointType::EndTime, 1}
};

// time begin -1, time end 1
std::pair<int, int> FindInterval(int t0, const std::unordered_set<std::string>& users, const std::multimap<int, timePoint>& points, int duration) {
    int curTime = t0;
    int point_sum = 0;

    std::unordered_map<std::string, int> MeetEnd;
    auto point_iterator = points.lower_bound(t0);

    for (auto it = point_iterator; it != points.end(); ++it) {
        //если точка принадлежит юзерам
        if (users.find(it->second.UserName) != users.end()) {
            //точка конца встречи, начало которой не попало в t0
            if (point_sum == 0 && point_sign[it->second.PT] > 0) {
                curTime = it->first;  
            } else  { //то что мы ищем, все предыдущие встречи закончились, начинается новая встреча
                if (it->first - curTime >= duration) {
                    return std::pair<int, int>{curTime, it->first};
                }
                curTime = it->first;
                point_sum += point_sign[it->second.PT];
            }  
        }
    }

    return std::pair<int, int>{curTime, std::numeric_limits<int>::max()};
}
 

int main() {

    std::multimap<int, timePoint> points;
    std::unordered_set<std::string> users{"user3", "user4"};

    points.insert({18, timePoint{"user1", PointType::BeginTime}});
    points.insert({22, timePoint{"user1", PointType::EndTime}});

    points.insert({18, timePoint{"user2", PointType::BeginTime}});
    points.insert({22, timePoint{"user2", PointType::EndTime}});

    points.insert({19, timePoint{"user3", PointType::BeginTime}});
    points.insert({23, timePoint{"user3", PointType::EndTime}});

    points.insert({19, timePoint{"user4", PointType::BeginTime}});
    points.insert({23, timePoint{"user4", PointType::EndTime}});

    points.insert({26, timePoint{"user1", PointType::BeginTime}});
    points.insert({28, timePoint{"user1", PointType::EndTime}});

    points.insert({26, timePoint{"user4", PointType::BeginTime}});
    points.insert({28, timePoint{"user4", PointType::EndTime}});

    points.insert({35, timePoint{"user3", PointType::BeginTime}});
    points.insert({36, timePoint{"user3", PointType::EndTime}});

    points.insert({35, timePoint{"user4", PointType::BeginTime}});
    points.insert({36, timePoint{"user4", PointType::EndTime}});

    //[1]
    auto time_pair = FindInterval(20, {"user3", "user4"}, points, 3);
    std::cout << time_pair.first << " " << time_pair.second << std::endl;
    //[2]
    time_pair = FindInterval(20, {"user3", "user4"}, points, 4);
    std::cout << time_pair.first << " " << time_pair.second << std::endl;
    //[3]
    time_pair = FindInterval(20, {"user3", "user4"}, points, 7);
    std::cout << time_pair.first << " " << time_pair.second << std::endl;
    //[4]
    time_pair = FindInterval(20, {"user3", "user4"}, points, 8);
    std::cout << time_pair.first << " " << time_pair.second << std::endl;
    //[5]
    time_pair = FindInterval(20, {"user1", "user2"}, points, 3);
    std::cout << time_pair.first << " " << time_pair.second << std::endl;
    //[6]
    time_pair = FindInterval(20, {"user1", "user2"}, points, 4);
    std::cout << time_pair.first << " " << time_pair.second << std::endl;
    //[7]
    time_pair = FindInterval(20, {"user1", "user2"}, points, 5);
    std::cout << time_pair.first << " " << time_pair.second << std::endl;
    //[8]
    time_pair = FindInterval(20, {"user2", "user3"}, points, 3);
    std::cout << time_pair.first << " " << time_pair.second << std::endl;
    //[9]
    time_pair = FindInterval(20, {"user2", "user3"}, points, 7);
    std::cout << time_pair.first << " " << time_pair.second << std::endl;
    //[10]
    time_pair = FindInterval(20, {"user2", "user3"}, points, 17);
    std::cout << time_pair.first << " " << time_pair.second << std::endl;

    return 0;
}