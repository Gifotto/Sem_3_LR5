#pragma once

// Абстрактная команда
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};

#include "Cave.h"

// Команда: выполнить один шаг симуляции
class StepCommand : public Command {
private:
    Cave& cave;

public:
    StepCommand(Cave& caveRef) : cave(caveRef) {}

    void execute() override {
        cave.doSimulationStep();
    }
};

// Команда: заново сгенерировать пещеру
class ResetCommand : public Command {
private:
    Cave& cave;

public:
    ResetCommand(Cave& caveRef) : cave(caveRef) {}

    void execute() override {
        cave.randomInitialize();
    }
};