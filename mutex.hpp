#pragma once
#include <shared_mutex>
#include <mutex>

typedef std::shared_timed_mutex Lock;
typedef std::unique_lock<Lock> WriteLock;
typedef std::shared_lock<Lock> ReadLock;