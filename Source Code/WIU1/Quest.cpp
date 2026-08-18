#include "Quest.h"

void Quest::completeQuest() {
    Completed = true;
}

bool Quest::isCompleted() const {
    return Completed;
}