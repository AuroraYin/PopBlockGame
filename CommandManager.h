#pragma once
#include"Command.h"
#include<stack>

using namespace std;

class BaseCommandManager
{
public:
	virtual ~BaseCommandManager() {}
	virtual void CallCommand(BaseCommand * pCommand) = 0;
	virtual void ClearAllCommands() = 0;
	virtual bool Undo(int*(&intcommand),BaseCommand*) = 0;
	virtual bool Redo(int*(&intcommand),BaseCommand*) = 0;
	virtual bool CanUndo() = 0;
	virtual bool CanRedo() = 0;
};

class CommandManager : public BaseCommandManager {
public:
	bool CanUndo();
	bool CanRedo();
	void CallCommand(BaseCommand * pCommand);
	void ClearAllCommands();
	bool Undo(int*(&intcommand),BaseCommand*);
	bool Redo(int*(&intcommand),BaseCommand*);
	
private:
	stack<BaseCommand*> stackUndo;
	stack<BaseCommand*> stackRedo;
	BaseCommand* PopUndoCommand();
	BaseCommand* PopRedoCommand();
	void DeleteUndoCommand();
	void DeleteRedoCommand();
	void PushUndoCommand(BaseCommand*pCommand);
	void PushRedoCommand(BaseCommand*pCommand);
	
};

