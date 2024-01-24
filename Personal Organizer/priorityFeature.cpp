#include<string>
using namespace std;
//Feature Classes
class PriorityFeature {
private:
    int priority;

public:
    //constructor
    PriorityFeature(int prioritySetter = -1) : priority(prioritySetter) {}

    //setter function
    void setPriority(int prioritySetter) {
        priority = prioritySetter;
    }

    //getter function
    int getPriority() const {
        return priority;
    }

    void resetPriority() {
        priority = -1;
    }

    //operator overloads
    bool operator<(const PriorityFeature& other) const {
        return priority < other.priority;
    }

    bool operator>(const PriorityFeature& other) const {
        return priority > other.priority;
    }

    bool isValidPriority() const {
        return (priority >= 0) && (priority <= 2);
    }

    //mapping priority
    string mapPriorityToLabel(int priority) const {
        switch (priority) {
        case 0:
            return "Low";
        case 1:
            return "Medium";
        case 2:
            return "High";
        default:
            return "Unknown Priority";
        }
    }

    string getPriorityLabel() const {
        return mapPriorityToLabel(priority);
    }

};
