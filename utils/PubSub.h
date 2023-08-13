//
// Created by 陈嘉乐 on 2023/8/12.
//

#ifndef CHATGPT_SIDEBAR_PUBSUB_H
#define CHATGPT_SIDEBAR_PUBSUB_H

#include <functional>
#include <map>
#include <algorithm>
typedef int SubscriberId;
template <typename... Args>
class Publisher {
public:

    typedef std::function<void(Args...)> CallbackType;
    SubscriberId subscriberId = 0;
    SubscriberId RegisterObserver(CallbackType subscriber) {
        subscriberMap[subscriberId] = subscriber;
        return subscriberId++;
    }

    void RemoveObserver(SubscriberId id) {
        if (subscriberMap.find(id) != subscriberMap.end()) {
            subscriberMap.erase(id);
        }
    }

    void Notify(Args... args) {
        for (auto& item : subscriberMap) {
            item.second(args...);
        }
    }

private:
    std::map<SubscriberId, CallbackType> subscriberMap;
};



#endif //CHATGPT_SIDEBAR_PUBSUB_H
