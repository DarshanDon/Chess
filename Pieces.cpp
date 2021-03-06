#include "stdafx.h"
#include "Pieces.h"
#include "Board.h"

Position::Position() {}

Position::Position(int x, int y) {
	this->x = x;
	this->y = y;
}

int Position::getRow() {
	return x;
}

int Position::getColumn() {
	return y;
}

bool Position::equals(Position position) {
	if (position.getRow() == this->getRow() && position.getColumn() == this->getColumn())
		return true;

	return false;
}

string Position::toString() {
	return "<" + to_string(getRow()) + " " + to_string(getColumn()) + ">";
}



Piece::Piece() {}

int Piece::getColor() {
	return color;
}

bool Piece::belongsTo(int playerColor) {
	if (getColor() == playerColor)
		return true;

	return false;
}

void Piece::addPositionAlong(Board board, Position currentPosition, int stepRow, int stepColumn) {
	int currentRow = currentPosition.getRow();
	int currentColumn = currentPosition.getColumn();
	Position newPosition;

	newPosition = Position(currentRow + stepRow, currentColumn + stepColumn);
	while (board.isInRange(newPosition) && !board.containsPieceAt(newPosition)) {
		validMoves.push_back(newPosition);
		newPosition = Position(newPosition.getRow() + stepRow, newPosition.getColumn() + stepColumn);
	}

	if (board.isInRange(newPosition) && !board.getPieceAt(newPosition)->belongsTo(color))
		validMoves.push_back(newPosition);
}

void Piece::addPositionAt(Board board, Position position) {

	if (board.isInRange(position) && !board.containsPieceAt(position))
		validMoves.push_back(position);
	else if (board.isInRange(position) && !board.getPieceAt(position)->belongsTo(color))
		validMoves.push_back(position);
}



Pawn::Pawn(int color) {
	this->color = color;
}

vector<Position> Pawn::getValidMoves(Board board, Position currentPosition) {
	validMoves.clear();

	int currentRow = currentPosition.getRow();
	int currentColumn = currentPosition.getColumn();

	if (this->color == COLOR_BLACK) {

		addPositionAt(board, Position(currentRow + 1, currentColumn));
		addPositionToCapture(board, Position(currentRow + 1, currentColumn + 1));
		addPositionToCapture(board, Position(currentRow + 1, currentColumn - 1));

		if (currentRow == 1 && !board.containsPieceAt(Position(currentRow + 1, currentColumn)))
			addPositionAt(board, Position(currentRow + 2, currentColumn));

	} else if (this->color == COLOR_WHITE) {

		addPositionAt(board, Position(currentRow - 1, currentColumn));
		addPositionToCapture(board, Position(currentRow - 1, currentColumn - 1));
		addPositionToCapture(board, Position(currentRow - 1, currentColumn + 1));

		if (currentRow == 6 && !board.containsPieceAt(Position(currentRow - 1, currentColumn)))
			addPositionAt(board, Position(currentRow - 2, currentColumn));
	}

	return validMoves;
}

void Pawn::addPositionAt(Board board, Position position) {
	if (board.isInRange(position) && !board.containsPieceAt(position))
		validMoves.push_back(position);
}

void Pawn::addPositionToCapture(Board board, Position position) {
	if (board.isInRange(position) && board.containsPieceAt(position) && !board.getPieceAt(position)->belongsTo(color))
		validMoves.push_back(position);
}



Knight::Knight(int color) {
	this->color = color;
}

vector<Position> Knight::getValidMoves(Board board, Position currentPosition) {
	validMoves.clear();

	int currentRow = currentPosition.getRow();
	int currentColumn = currentPosition.getColumn();
	Position newPosition;

	int stepColumn = 1;
	for (int row = currentRow - 2; row <= currentRow + 2; row++) {

		if (row == currentRow) {
			stepColumn--;
			stepColumn = -stepColumn;
			continue;
		}

		newPosition = Position(row, currentColumn + stepColumn);
		addPositionAt(board, newPosition);

		newPosition = Position(row, currentColumn - stepColumn);
		addPositionAt(board, newPosition);

		stepColumn++;
	}

	return validMoves;
}



Bishop::Bishop(int color) {
	this->color = color;
}

vector<Position> Bishop::getValidMoves(Board board, Position currentPosition) {
	validMoves.clear();

	addPositionAlong(board, currentPosition, 1, 1);
	addPositionAlong(board, currentPosition, 1, -1);
	addPositionAlong(board, currentPosition, -1, 1);
	addPositionAlong(board, currentPosition, -1, -1);

	return validMoves;
}



Rook::Rook(int color) {
	this->color = color;
}

vector<Position> Rook::getValidMoves(Board board, Position currentPosition) {
	validMoves.clear();

	addPositionAlong(board, currentPosition, 1, 0);
	addPositionAlong(board, currentPosition, 0, 1);
	addPositionAlong(board, currentPosition, -1, 0);
	addPositionAlong(board, currentPosition, 0, -1);

	return validMoves;
}



Queen::Queen(int color) {
	this->color = color;
}

vector<Position> Queen::getValidMoves(Board board, Position currentPosition) {
	validMoves.clear();

	addPositionAlong(board, currentPosition, 1, 1);
	addPositionAlong(board, currentPosition, 1, -1);
	addPositionAlong(board, currentPosition, -1, 1);
	addPositionAlong(board, currentPosition, -1, -1);
	addPositionAlong(board, currentPosition, 1, 0);
	addPositionAlong(board, currentPosition, 0, 1);
	addPositionAlong(board, currentPosition, -1, 0);
	addPositionAlong(board, currentPosition, 0, -1);

	return validMoves;
}



King::King(int color) {
	this->color = color;
}

vector<Position> King::getValidMoves(Board board, Position currentPosition) {
	validMoves.clear();

	int currentRow = currentPosition.getRow();
	int currentColumn = currentPosition.getColumn();
	Position newPosition;

	for (int row = currentRow - 1; row <= currentRow + 1; row++)
		for (int column = currentColumn - 1; column <= currentColumn + 1; column++) {
			newPosition = Position(row, column);
			addPositionAt(board, newPosition);
		}

	return validMoves;
}