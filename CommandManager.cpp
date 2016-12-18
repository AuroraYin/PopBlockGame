#include"CommandManager.h"

void CommandManager::PushUndoCommand(BaseCommand * pCommand)
{
	stackUndo.push(pCommand);
}

BaseCommand* CommandManager::PopUndoCommand()
{
	BaseCommand*pCommand = stackUndo.top();
	stackUndo.pop();
	return pCommand;
}

void CommandManager::PushRedoCommand(BaseCommand * pCommand)
{
	stackRedo.push(pCommand);
}

BaseCommand* CommandManager::PopRedoCommand()
{
	BaseCommand*pCommand = stackRedo.top();
	stackRedo.pop();
	return pCommand;
}

void CommandManager::DeleteUndoCommand()
{
	int iSize = stackUndo.size();
	for (int i = 0; i < iSize; i++)
	{
		stackUndo.pop();
	}
}

void CommandManager::DeleteRedoCommand()
{
	int iSize = stackRedo.size();
	for (int i = 0; i < iSize; i++)
	{
		stackRedo.pop();
	}

}

bool CommandManager::CanUndo() {
	if (stackUndo.empty())return false;
	else return true;
}

bool CommandManager::CanRedo() {
	if (stackRedo.empty())return false;
	else return true;
}

void CommandManager::CallCommand(BaseCommand * pCommand) {
	PushUndoCommand(pCommand);
}

void CommandManager::ClearAllCommands() {
	DeleteRedoCommand();
	//DeleteUndoCommand();
}

bool CommandManager::Undo(int * (&intcommand),BaseCommand*toPush)
{
	if (CanUndo() == false)return false;
	else
	{
		BaseCommand*bc = PopUndoCommand();
		intcommand = bc->Unexecute();
		//PushRedoCommand(bc);
		PushRedoCommand(toPush);
		return true;
	}
}

bool CommandManager::Redo(int *(& intcommand),BaseCommand*ToPush)
{
	if (CanRedo() == false)return false;
	else
	{
		BaseCommand*bc=PopRedoCommand();
		intcommand = bc->Execute();
		//PushUndoCommand(bc);
		PushUndoCommand(ToPush);
		return true;
	}
	return false;
}

