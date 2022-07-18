#!/usr/bin/python3
import pygame
from pygame.locals import *
from random import seed
from random import choice
from datetime import datetime

ORANGE = (255, 161, 0)
WHITE = (255, 255, 255)
DARKGREY = (205, 193, 180)
LIGHTGREY = (187, 173, 160)

class Title:
    def __init__(self, window):
        self.font = pygame.font.SysFont(None, 250)
        self.img = self.font.render('2048', True, ORANGE)
        self.pos = ((window.get_rect().width/2) - (self.img.get_rect().width/2), 50)

class Board:
    def __init__(self, window):
        self.window = window
        self.color = DARKGREY
        self.tile_size = 150
        self.tile_between = 15
        self.small_board_size = self.tile_size * 4 + self.tile_between * 3
        self.full_board_size = self.tile_size * 4 + self.tile_between * 5
        self.x = ((self.window.get_rect().width/2) - ((self.small_board_size) / 2)) - self.tile_between
        self.y = ((self.window.get_rect().width/2) - ((self.small_board_size) / 2 + 200)) - self.tile_between
        self.width = self.full_board_size
        self.height = self.full_board_size
    def draw(self):
        pygame.draw.rect(self.window, self.color, (self.x, self.y, self.width, self.height))

class TileBoard(Board):
    def __init__(self, window):
        Board.__init__(self, window)
        self.tile_color = LIGHTGREY
    def draw(self):
        Board.draw(self)
        tile_x = (self.window.get_rect().width/2) - ((self.small_board_size) / 2)
        tile_y = (self.window.get_rect().width/2) - ((self.small_board_size) / 2 + 200)
        i = 0
        u = 0
        while i < 4:
            while u < 4:
                pygame.draw.rect(self.window, self.tile_color, (tile_x, tile_y, self.tile_size, self.tile_size))
                tile_x += self.tile_size + self.tile_between
                u += 1
            u = 0
            tile_x = (self.window.get_rect().width/2) - ((self.small_board_size) / 2)
            tile_y += self.tile_size + self.tile_between
            i += 1

class Tile:
    def __init__(self, x, y, window):
        self.window = window
        self.value = 2
        self.x = x
        self.y = y
        self.speed = 0
        self.width = 0
        self.height = 0
        self.stackable = True
        self.next = 0
        self.tilesColors = {
            2:(238, 228, 218), 
            4:(237, 224, 200),
            8:(242, 177, 121),
            16:(245, 149, 99),
            32:(246, 125, 95),
            64:(246, 94, 59),
            128:(237, 207, 114),
            256:(237, 204, 97),
            512:(237, 200, 80),
            1024:(236, 196, 64),
            2048:(235, 192, 48)
        }
        self.textColors = (
            (249, 246, 242),
            (119, 110, 101)
        )
        self.fontSizes = {
            2:100,
            4:100,
            8:100,
            16:90,
            32:90,
            64:90,
            128:80,
            256:80,
            512:80,
            1024:60,
            2048:60
        }
    def getX(self):
        return self.x
    def getY(self):
        return self.y
    def getValue(self):
        return self.value
    def getSpeed(self):
        return (self.speed)
    def getNext(self):
        return (self.next)
    def isStackable(self):
        return (self.stackable)
    def setPos(self, x, y):
        self.x = x
        self.y = y
    def setValue(self, value):
        self.value = value
    def setStackable(self, stackable):
        self.stackable = stackable
    def setSpeed(self, speed):
        self.speed = speed
    def setNext(self, next):
        self.next = next
    def draw(self):
        color = self.tilesColors[self.value]
        text = str(self.value)
        font_size = self.fontSizes[self.value]
        font = pygame.font.SysFont(None, font_size)
        text_color = self.textColors[1] if self.value == 2 or self.value == 4 else self.textColors[0]
        img = font.render(text, True, text_color)
        pos = (self.x + (150 / 2) - (img.get_rect().width / 2), self.y + (150 / 2) - (img.get_rect().height / 2))

        pygame.draw.rect(self.window, color, (self.x, self.y, 150, 150))
        self.window.blit(img, pos)

class GameTiles(TileBoard):
    def setOneColumnFromLines(self, x_index):
        col = []

        for tile in self.line1:
            if tile.getX() == x_index:
                col.append(tile)
        for tile in self.line2:
            if tile.getX() == x_index:
                col.append(tile)
        for tile in self.line3:
            if tile.getX() == x_index:
                col.append(tile)
        for tile in self.line4:
            if tile.getX() == x_index:
                col.append(tile)
        return col
    def setColumnsFromLines(self):
        x_index = self.min_x

        self.column1 = self.setOneColumnFromLines(x_index)
        x_index += self.tile_between + self.tile_size
        self.column2 = self.setOneColumnFromLines(x_index)
        x_index += self.tile_between + self.tile_size
        self.column3 = self.setOneColumnFromLines(x_index)
        x_index += self.tile_between + self.tile_size
        self.column4 = self.setOneColumnFromLines(x_index)
    def setOneLineFromColumns(self, y_index):
        line = []

        for tile in self.column1:
            if tile.getY() == y_index:
                line.append(tile)
        for tile in self.column2:
            if tile.getY() == y_index:
                line.append(tile)
        for tile in self.column3:
            if tile.getY() == y_index:
                line.append(tile)
        for tile in self.column4:
            if tile.getY() == y_index:
                line.append(tile)
        return line
    def setLinesFromColumns(self):
        y_index = self.min_y

        self.line1 = self.setOneLineFromColumns(y_index)
        y_index += self.tile_between + self.tile_size
        self.line2 = self.setOneLineFromColumns(y_index)
        y_index += self.tile_between + self.tile_size
        self.line3 = self.setOneLineFromColumns(y_index)
        y_index += self.tile_between + self.tile_size
        self.line4 = self.setOneLineFromColumns(y_index)
    def generateTile(self):
        chose_x = 0
        chose_y = 0
        possibles_x = []
        possibles_y = []
        tiles1 = True
        tiles2 = True
        tiles3 = True
        tiles4 = True

        x_index = self.min_x
        while (x_index <= self.max_x):
            tiles1 = True
            tiles2 = True
            tiles3 = True
            tiles4 = True
            for tile in self.line1:
                if tile.getX() == x_index:
                    tiles1 = False
            for tile in self.line2:
                if tile.getX() == x_index:
                    tiles2 = False
            for tile in self.line3:
                if tile.getX() == x_index:
                    tiles3 = False
            for tile in self.line4:
                if tile.getX() == x_index:
                    tiles4 = False
            if (tiles1 == True or
                tiles2 == True or
                tiles3 == True or
                tiles4 == True):
                possibles_x.append(x_index)
            x_index += self.tile_size + self.tile_between
        chose_x = choice(possibles_x)
        tiles1 = True
        tiles2 = True
        tiles3 = True
        tiles4 = True
        for tile in self.line1:
            if tile.getX() == chose_x and tile.getY() == self.min_y:
                tiles1 = False
        for tile in self.line2:
            if tile.getX() == chose_x and tile.getY() == self.min_y + self.tile_between + self.tile_size:
                tiles2 = False
        for tile in self.line3:
            if tile.getX() == chose_x and tile.getY() == self.min_y + ((self.tile_between + self.tile_size) * 2):
                tiles3 = False
        for tile in self.line4:
            if tile.getX() == chose_x and tile.getY() == self.max_y:
                tiles4 = False
        if (tiles1 == True):
            possibles_y.append(self.min_y)
        if (tiles2 == True):
            possibles_y.append(self.min_y + self.tile_between + self.tile_size)
        if (tiles3 == True):
            possibles_y.append(self.min_y + ((self.tile_between + self.tile_size) * 2))
        if (tiles4 == True):
            possibles_y.append(self.max_y)
        chose_y = choice(possibles_y)
        if (chose_y == self.min_y):
            self.line1.append(Tile(chose_x, chose_y, self.window))
        if (chose_y == self.min_y + self.tile_between + self.tile_size):
            self.line2.append(Tile(chose_x, chose_y, self.window))
        if (chose_y == self.min_y + ((self.tile_between + self.tile_size) * 2)):
            self.line3.append(Tile(chose_x, chose_y, self.window))
        if (chose_y == self.max_y):
            self.line4.append(Tile(chose_x, chose_y, self.window))
        self.setColumnsFromLines()
        self.setLinesFromColumns()
    def __init__(self, window):
        TileBoard.__init__(self, window)
        self.tile_between = 15
        self.tile_size = 150
        self.min_x = (self.window.get_rect().width/2) - ((self.small_board_size) / 2)
        self.max_x = self.min_x + ((self.tile_size + self.tile_between) * 3)
        self.min_y = (self.window.get_rect().width/2) - ((self.small_board_size) / 2 + 200)
        self.max_y = self.min_y + ((self.tile_size + self.tile_between) * 3)
        self.line1 = []
        self.line2 = []
        self.line3 = []
        self.line4 = []
        self.column1 = []
        self.column2 = []
        self.column3 = []
        self.column4 = []
        self.sliding = False
        self.slideUp = False
        self.slideDown = False
        self.slideLeft = False
        self.slideRight = False
        self.score = 0
    def getScore(self):
        return (self.score)
    def draw(self):
        TileBoard.draw(self)
        if (self.slideLeft == True or self.slideRight == True):
            for tile in self.line1:
                tile.draw()
            for tile in self.line2:
                tile.draw()
            for tile in self.line3:
                tile.draw()
            for tile in self.line4:
                tile.draw()
        else:
            for tile in self.column1:
                tile.draw()
            for tile in self.column2:
                tile.draw()
            for tile in self.column3:
                tile.draw()
            for tile in self.column4:
                tile.draw()
    def slideLeft_setSpeedAndNextPos(self, tmp_line, tile):
        move_number = 0 if tile.getX() == self.min_x else 1 if tile.getX() == (self.min_x + self.tile_between + self.tile_size) else 2 if tile.getX() == (self.min_x + ((self.tile_between + self.tile_size) * 2)) else 3
        index = 0

        for tmp_tile in tmp_line:
            if tmp_tile.getX() < tile.getX():
                move_number -= 1
        while index < len(tmp_line):
            if tmp_line[index].getX == tile.getX:
                break
            index += 1
        if (index != 0 and tmp_line[index - 1].isStackable() == True and tmp_line[index - 1].getValue() == tile.getValue()):
            move_number += 1
            if (tile.getX() - ((self.tile_between + self.tile_size) * move_number) > tmp_line[index - 1].getNext()):
                move_number += 1
            tile.setStackable(False)
        if (index != 0 and tmp_line[index - 1].isStackable() == False):
            move_number += 1
        tile.setSpeed(move_number)
        tile.setNext(tile.getX() - ((self.tile_between + self.tile_size) * move_number))
    def slideLeft_setPos(self, tile):
        end = True

        if (tile.getX() > tile.getNext()):
            end = False
            tile.setPos(tile.getX() - (tile.getSpeed() * 20), tile.getY())
        else:
            tile.setPos(tile.getNext(), tile.getY())
        return end
    def slideLeft_stackLine(self, line):
        index = 0

        if len(line) < 2:
            return
        while index < len(line):
            if (line[index].isStackable() == False):
                line[index].setValue(line[index].getValue() * 2)
                line[index].setStackable(True)
                line.remove(line[index - 1])
                self.score += line[index - 1].getValue()
            index += 1
    def slideLeft_stackTiles(self):
        self.slideLeft_stackLine(self.line1)
        self.slideLeft_stackLine(self.line2)
        self.slideLeft_stackLine(self.line3)
        self.slideLeft_stackLine(self.line4)
        self.setColumnsFromLines()
    def slideTilesLeft(self):
        if (self.slideLeft == False):
            self.sliding = True
            self.slideLeft = True

            for tile in self.line1:
                self.slideLeft_setSpeedAndNextPos(self.line1, tile)
            for tile in self.line2:
                self.slideLeft_setSpeedAndNextPos(self.line2, tile)
            for tile in self.line3:
                self.slideLeft_setSpeedAndNextPos(self.line3, tile)
            for tile in self.line4:
                self.slideLeft_setSpeedAndNextPos(self.line4, tile)
        else:
            end = True

            for tile in self.line1:
                if (self.slideLeft_setPos(tile) == False):
                    end = False
            for tile in self.line2:
                if (self.slideLeft_setPos(tile) == False):
                    end = False
            for tile in self.line3:
                if (self.slideLeft_setPos(tile) == False):
                    end = False
            for tile in self.line4:
                if (self.slideLeft_setPos(tile) == False):
                    end = False
            if end == True:
                self.sliding = False
                self.slideLeft = False
                self.setColumnsFromLines()
                self.setLinesFromColumns()
                self.slideLeft_stackTiles()
                self.generateTile()
    def slideRight_setSpeedAndNextPos(self, tmp_line, tile):
        move_number = 0 if tile.getX() == self.max_x else 1 if tile.getX() == (self.max_x - (self.tile_between + self.tile_size)) else 2 if tile.getX() == (self.max_x - ((self.tile_between + self.tile_size) * 2)) else 3
        index = 0

        for tmp_tile in tmp_line:
            if tmp_tile.getX() > tile.getX():
                move_number -= 1
        while index < len(tmp_line):
            if tmp_line[index].getX == tile.getX:
                break
            index += 1
        if (index != len(tmp_line) - 1 and tmp_line[index + 1].isStackable() == True and
            tmp_line[index + 1].getValue() == tile.getValue()):
            move_number += 1
            if (tile.getX() + ((self.tile_between + self.tile_size) * move_number) < tmp_line[index + 1].getNext()):
                move_number += 1
            tile.setStackable(False)
        if (index != len(tmp_line) - 1 and tmp_line[index + 1].isStackable() == False):
            move_number += 1
        tile.setSpeed(move_number)
        tile.setNext(tile.getX() + ((self.tile_between + self.tile_size) * move_number))
    def slideRight_setPos(self, tile):
        end = True

        if (tile.getX() < tile.getNext()):
            end = False
            tile.setPos(tile.getX() + (tile.getSpeed() * 20), tile.getY())
        else:
            tile.setPos(tile.getNext(), tile.getY())
        return end
    def slideRight_stackLine(self, line):
        index = len(line) - 1

        if len(line) < 2:
            return
        while index >= 0:
            if (line[index].isStackable() == False):
                line[index].setValue(line[index].getValue() * 2)
                line[index].setStackable(True)
                line.remove(line[index + 1])
                self.score += line[index].getValue()
            index -= 1
    def slideRight_stackTiles(self):
        self.slideRight_stackLine(self.line1)
        self.slideRight_stackLine(self.line2)
        self.slideRight_stackLine(self.line3)
        self.slideRight_stackLine(self.line4)
        self.setColumnsFromLines()
    def slideTilesRight(self):
        if (self.slideRight == False):
            self.sliding = True
            self.slideRight = True

            index = len(self.line1) - 1
            while index >= 0:
                self.slideRight_setSpeedAndNextPos(self.line1, self.line1[index])
                index -= 1
            index = len(self.line2) - 1
            while index >= 0:
                self.slideRight_setSpeedAndNextPos(self.line2, self.line2[index])
                index -= 1
            index = len(self.line3) - 1
            while index >= 0:
                self.slideRight_setSpeedAndNextPos(self.line3, self.line3[index])
                index -= 1
            index = len(self.line4) - 1
            while index >= 0:
                self.slideRight_setSpeedAndNextPos(self.line4, self.line4[index])
                index -= 1
        else:
            end = True

            for tile in self.line1:
                if (self.slideRight_setPos(tile) == False):
                    end = False
            for tile in self.line2:
                if (self.slideRight_setPos(tile) == False):
                    end = False
            for tile in self.line3:
                if (self.slideRight_setPos(tile) == False):
                    end = False
            for tile in self.line4:
                if (self.slideRight_setPos(tile) == False):
                    end = False
            if end == True:
                self.sliding = False
                self.slideRight = False
                self.setColumnsFromLines()
                self.setLinesFromColumns()
                self.slideRight_stackTiles()
                self.generateTile()
    def slideUp_setSpeedAndNextPos(self, tmp_col, tile):
        move_number = 0 if tile.getY() == self.min_y else 1 if tile.getY() == (self.min_y + self.tile_between + self.tile_size) else 2 if tile.getY() == (self.min_y + ((self.tile_between + self.tile_size) * 2)) else 3
        index = 0

        for tmp_tile in tmp_col:
            if tmp_tile.getY() < tile.getY():
                move_number -= 1
        while index < len(tmp_col):
            if tmp_col[index].getY == tile.getY:
                break
            index += 1
        if (index != 0 and tmp_col[index - 1].isStackable() == True and tmp_col[index - 1].getValue() == tile.getValue()):
            move_number += 1
            if (tile.getY() - ((self.tile_between + self.tile_size) * move_number) > tmp_col[index - 1].getNext()):
                move_number += 1
            tile.setStackable(False)
        if (index != 0 and tmp_col[index - 1].isStackable() == False):
            move_number += 1
        tile.setSpeed(move_number)
        tile.setNext(tile.getY() - ((self.tile_between + self.tile_size) * move_number))
    def slideUp_setPos(self, tile):
        end = True

        if (tile.getY() > tile.getNext()):
            end = False
            tile.setPos(tile.getX(), tile.getY() - (tile.getSpeed() * 20))
        else:
            tile.setPos(tile.getX(), tile.getNext())
        return end
    def slideUp_stackCol(self, column):
        index = 0

        if len(column) < 2:
            return
        while index < len(column):
            if (column[index].isStackable() == False):
                column[index].setValue(column[index].getValue() * 2)
                column[index].setStackable(True)
                column.remove(column[index - 1])
                self.score += column[index - 1].getValue()
            index += 1
    def slideUp_stackTiles(self):
        self.slideUp_stackCol(self.column1)
        self.slideUp_stackCol(self.column2)
        self.slideUp_stackCol(self.column3)
        self.slideUp_stackCol(self.column4)
        self.setLinesFromColumns()
    def slideTilesUp(self):
        if (self.slideUp == False):
            self.sliding = True
            self.slideUp = True

            for tile in self.column1:
                self.slideUp_setSpeedAndNextPos(self.column1, tile)
            for tile in self.column2:
                self.slideUp_setSpeedAndNextPos(self.column2, tile)
            for tile in self.column3:
                self.slideUp_setSpeedAndNextPos(self.column3, tile)
            for tile in self.column4:
                self.slideUp_setSpeedAndNextPos(self.column4, tile)
        else:
            end = True

            for tile in self.column1:
                if (self.slideUp_setPos(tile) == False):
                    end = False
            for tile in self.column2:
                if (self.slideUp_setPos(tile) == False):
                    end = False
            for tile in self.column3:
                if (self.slideUp_setPos(tile) == False):
                    end = False
            for tile in self.column4:
                if (self.slideUp_setPos(tile) == False):
                    end = False
            if end == True:
                self.sliding = False
                self.slideUp = False
                self.setLinesFromColumns()
                self.setColumnsFromLines()
                self.slideUp_stackTiles()
                self.generateTile()
    def slideDown_setSpeedAndNextPos(self, tmp_col, tile):
        move_number = 0 if tile.getY() == self.max_y else 1 if tile.getY() == (self.max_y - (self.tile_between + self.tile_size)) else 2 if tile.getY() == (self.max_y - ((self.tile_between + self.tile_size) * 2)) else 3
        index = 0

        for tmp_tile in tmp_col:
            if tmp_tile.getY() > tile.getY():
                move_number -= 1
        while index < len(tmp_col):
            if tmp_col[index].getY == tile.getY:
                break
            index += 1
        if (index != len(tmp_col) - 1 and tmp_col[index + 1].isStackable() == True and
            tmp_col[index + 1].getValue() == tile.getValue()):
            move_number += 1
            if (tile.getY() + ((self.tile_between + self.tile_size) * move_number) < tmp_col[index + 1].getNext()):
                move_number += 1
            tile.setStackable(False)
        if (index != len(tmp_col) - 1 and tmp_col[index + 1].isStackable() == False):
            move_number += 1
        tile.setSpeed(move_number)
        tile.setNext(tile.getY() + ((self.tile_between + self.tile_size) * move_number))
    def slideDown_setPos(self, tile):
        end = True

        if (tile.getY() < tile.getNext()):
            end = False
            tile.setPos(tile.getX(), tile.getY() + (tile.getSpeed() * 20))
        else:
            tile.setPos(tile.getX(), tile.getNext())
        return end
    def slideDown_stackColumn(self, column):
        index = len(column) - 1

        if len(column) < 2:
            return
        while index >= 0:
            if (column[index].isStackable() == False):
                column[index].setValue(column[index].getValue() * 2)
                column[index].setStackable(True)
                column.remove(column[index + 1])
                self.score += column[index].getValue()
            index -= 1
    def slideDown_stackTiles(self):
        self.slideDown_stackColumn(self.column1)
        self.slideDown_stackColumn(self.column2)
        self.slideDown_stackColumn(self.column3)
        self.slideDown_stackColumn(self.column4)
        self.setLinesFromColumns()
    def slideTilesDown(self):
        if (self.slideDown == False):
            self.sliding = True
            self.slideDown = True

            index = len(self.column1) - 1
            while index >= 0:
                self.slideDown_setSpeedAndNextPos(self.column1, self.column1[index])
                index -= 1
            index = len(self.column2) - 1
            while index >= 0:
                self.slideDown_setSpeedAndNextPos(self.column2, self.column2[index])
                index -= 1
            index = len(self.column3) - 1
            while index >= 0:
                self.slideDown_setSpeedAndNextPos(self.column3, self.column3[index])
                index -= 1
            index = len(self.column4) - 1
            while index >= 0:
                self.slideDown_setSpeedAndNextPos(self.column4, self.column4[index])
                index -= 1
        else:
            end = True

            for tile in self.column1:
                if (self.slideDown_setPos(tile) == False):
                    end = False
            for tile in self.column2:
                if (self.slideDown_setPos(tile) == False):
                    end = False
            for tile in self.column3:
                if (self.slideDown_setPos(tile) == False):
                    end = False
            for tile in self.column4:
                if (self.slideDown_setPos(tile) == False):
                    end = False
            if end == True:
                self.sliding = False
                self.slideDown = False
                self.setLinesFromColumns()
                self.setColumnsFromLines()
                self.slideDown_stackTiles()
                self.generateTile()
    def checkLeftSlide_checkTile(self, tmp_line, tile):
        move_number = 0 if tile.getX() == self.min_x else 1 if tile.getX() == (self.min_x + self.tile_between + self.tile_size) else 2 if tile.getX() == (self.min_x + ((self.tile_between + self.tile_size) * 2)) else 3
        index = 0

        for tmp_tile in tmp_line:
            if tmp_tile.getX() < tile.getX():
                move_number -= 1
        while index < len(tmp_line):
            if tmp_line[index].getX == tile.getX:
                break
            index += 1
        if (index != 0 and tmp_line[index - 1].isStackable() == True and tmp_line[index - 1].getValue() == tile.getValue()):
            move_number += 1
            if (tile.getX() - ((self.tile_between + self.tile_size) * move_number) > tmp_line[index - 1].getNext()):
                move_number += 1
        if (index != 0 and tmp_line[index - 1].isStackable() == False):
            move_number += 1
        return move_number
    def checkLeftSlide(self):
        canMove = False

        for tile in self.line1:
            if self.checkLeftSlide_checkTile(self.line1, tile) > 0:
                canMove = True
        for tile in self.line2:
            if self.checkLeftSlide_checkTile(self.line2, tile) > 0:
                canMove = True
        for tile in self.line3:
            if self.checkLeftSlide_checkTile(self.line3, tile) > 0:
                canMove = True
        for tile in self.line4:
            if self.checkLeftSlide_checkTile(self.line4, tile) > 0:
                canMove = True
        return canMove
    def checkRightSlide_checkTile(self, tmp_line, tile):
        move_number = 0 if tile.getX() == self.max_x else 1 if tile.getX() == (self.max_x - (self.tile_between + self.tile_size)) else 2 if tile.getX() == (self.max_x - ((self.tile_between + self.tile_size) * 2)) else 3
        index = 0

        for tmp_tile in tmp_line:
            if tmp_tile.getX() > tile.getX():
                move_number -= 1
        while index < len(tmp_line):
            if tmp_line[index].getX == tile.getX:
                break
            index += 1
        if (index != len(tmp_line) - 1 and tmp_line[index + 1].isStackable() == True and
            tmp_line[index + 1].getValue() == tile.getValue()):
            move_number += 1
            if (tile.getX() + ((self.tile_between + self.tile_size) * move_number) < tmp_line[index + 1].getNext()):
                move_number += 1
        if (index != len(tmp_line) - 1 and tmp_line[index + 1].isStackable() == False):
            move_number += 1
        return move_number
    def checkRightSlide(self):
        canMove = False

        index = len(self.line1) - 1
        while index >= 0:
            if self.checkRightSlide_checkTile(self.line1, self.line1[index]) > 0:
                canMove = True
            index -= 1
        index = len(self.line2) - 1
        while index >= 0:
            if self.checkRightSlide_checkTile(self.line2, self.line2[index]) > 0:
                canMove = True
            index -= 1
        index = len(self.line3) - 1
        while index >= 0:
            if self.checkRightSlide_checkTile(self.line3, self.line3[index]) > 0:
                canMove = True
            index -= 1
        index = len(self.line4) - 1
        while index >= 0:
            if self.checkRightSlide_checkTile(self.line4, self.line4[index]) > 0:
                canMove = True
            index -= 1
        return canMove
    def checkUpSlide_checkTile(self, tmp_col, tile):
        move_number = 0 if tile.getY() == self.min_y else 1 if tile.getY() == (self.min_y + self.tile_between + self.tile_size) else 2 if tile.getY() == (self.min_y + ((self.tile_between + self.tile_size) * 2)) else 3
        index = 0

        for tmp_tile in tmp_col:
            if tmp_tile.getY() < tile.getY():
                move_number -= 1
        while index < len(tmp_col):
            if tmp_col[index].getY == tile.getY:
                break
            index += 1
        if (index != 0 and tmp_col[index - 1].isStackable() == True and tmp_col[index - 1].getValue() == tile.getValue()):
            move_number += 1
            if (tile.getY() - ((self.tile_between + self.tile_size) * move_number) > tmp_col[index - 1].getNext()):
                move_number += 1
        if (index != 0 and tmp_col[index - 1].isStackable() == False):
            move_number += 1
        return move_number
    def checkUpSlide(self):
        canMove = False

        for tile in self.column1:
            if self.checkUpSlide_checkTile(self.column1, tile) > 0:
                canMove = True
        for tile in self.column2:
            if self.checkUpSlide_checkTile(self.column2, tile) > 0:
                canMove = True
        for tile in self.column3:
            if self.checkUpSlide_checkTile(self.column3, tile) > 0:
                canMove = True
        for tile in self.column4:
            if self.checkUpSlide_checkTile(self.column4, tile) > 0:
                canMove = True
        return canMove
    def checkDownSlide_checkTile(self, tmp_col, tile):
        move_number = 0 if tile.getY() == self.max_y else 1 if tile.getY() == (self.max_y - (self.tile_between + self.tile_size)) else 2 if tile.getY() == (self.max_y - ((self.tile_between + self.tile_size) * 2)) else 3
        index = 0

        for tmp_tile in tmp_col:
            if tmp_tile.getY() > tile.getY():
                move_number -= 1
        while index < len(tmp_col):
            if tmp_col[index].getY == tile.getY:
                break
            index += 1
        if (index != len(tmp_col) - 1 and tmp_col[index + 1].isStackable() == True and
            tmp_col[index + 1].getValue() == tile.getValue()):
            move_number += 1
            if (tile.getY() + ((self.tile_between + self.tile_size) * move_number) < tmp_col[index + 1].getNext()):
                move_number += 1
        if (index != len(tmp_col) - 1 and tmp_col[index + 1].isStackable() == False):
            move_number += 1
        return move_number
    def checkDownSlide(self):
        canMove = False

        index = len(self.column1) - 1
        while index >= 0:
            if self.checkDownSlide_checkTile(self.column1, self.column1[index]) > 0:
                canMove = True
            index -= 1
        index = len(self.column2) - 1
        while index >= 0:
            if self.checkDownSlide_checkTile(self.column2, self.column2[index]) > 0:
                canMove = True
            index -= 1
        index = len(self.column3) - 1
        while index >= 0:
            if self.checkDownSlide_checkTile(self.column3, self.column3[index]) > 0:
                canMove = True
            index -= 1
        index = len(self.column4) - 1
        while index >= 0:
            if self.checkDownSlide_checkTile(self.column4, self.column4[index]) > 0:
                canMove = True
            index -= 1
        return canMove
    def isGameOver(self):
        if self.checkDownSlide() == False and self.checkUpSlide() == False and self.checkLeftSlide() == False and self.checkRightSlide() == False:
            return True
        return False
    def isGameWon(self):
        for tile in self.line1:
            if tile.getValue() == 2048:
                return True
        for tile in self.line2:
            if tile.getValue() == 2048:
                return True
        for tile in self.line3:
            if tile.getValue() == 2048:
                return True
        for tile in self.line4:
            if tile.getValue() == 2048:
                return True
        return False
    def update(self):
        if self.slideLeft == True:
            self.slideTilesLeft()
        if self.slideRight == True:
            self.slideTilesRight()
        if self.slideUp == True:
            self.slideTilesUp()
        if self.slideDown == True:
            self.slideTilesDown()

pygame.init()
pygame.joystick.init()

window = pygame.display.set_mode((1680, 1050))
pygame.display.set_caption('2048')

title = Title(window)
gametiles = GameTiles(window)
gametiles.generateTile()

joysticks = [pygame.joystick.Joystick(x) for x in range (pygame.joystick.get_count())]
axes = joysticks[0].get_numaxes()

running = True
background = WHITE
clock = pygame.time.Clock()
while running:
    for event in pygame.event.get():
        if event.type == QUIT:
            running = False
        if event.type == KEYDOWN:
            if event.key == K_q and gametiles.sliding == False and gametiles.checkLeftSlide():
                gametiles.slideTilesLeft()
            if event.key == K_d and gametiles.sliding == False and gametiles.checkRightSlide():
                gametiles.slideTilesRight()
            if event.key == K_z and gametiles.sliding == False and gametiles.checkUpSlide():
                gametiles.slideTilesUp()
            if event.key == K_s and gametiles.sliding == False and gametiles.checkDownSlide():
                gametiles.slideTilesDown()
    for i in range(axes):
        axis = joysticks[0].get_axis(i)
        if axis < -0.5 and i == 0 and gametiles.sliding == False and gametiles.checkLeftSlide():
            gametiles.slideTilesLeft()
        if axis > 0.5 and i == 0 and gametiles.sliding == False and gametiles.checkRightSlide():
            gametiles.slideTilesRight()
        if axis < -0.5 and i == 1 and gametiles.sliding == False and gametiles.checkUpSlide():
            gametiles.slideTilesUp()
        if axis > 0.5 and i == 1 and gametiles.sliding == False and gametiles.checkDownSlide():
            gametiles.slideTilesDown()
            
    gametiles.update()
    window.fill(background)
    window.blit(title.img, title.pos)
    gametiles.draw()
    pygame.display.update()
    if gametiles.sliding == False and (gametiles.isGameWon() == True or gametiles.isGameOver() == True):
        print(gametiles.score)
        break
    clock.tick(60)
pygame.joystick.quit()
pygame.quit()