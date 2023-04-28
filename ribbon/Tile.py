# I hope the programming gods forgive me for the dogwater code that I have written here 🙏🏻

class Tile:
    def __init__(self, rows=1, colors=[]):
        self.rows = rows
        self.cols = int(len(colors)/rows)
        if rows > 1:
            if len(colors) % 2 != 0:
                raise ValueError("Number of colors must be even")
        self.rowslist = {}
        each_row_members = int(len(colors)/rows)
        for each_row in range(rows):
            self.rowslist.update({
                each_row: [
                    x for x in colors[:each_row_members]
                ]
            })
            for each_color in colors[:each_row_members]:
                colors.remove(each_color)

        self.colslist = {}
        for each_col in range(self.cols):
            self.colslist.update({
                each_col: []
            })
        index = 0
        for each_col in range(self.cols):
            for each_row in self.rowslist:
                self.colslist[index].append(self.rowslist[each_row][index])
            index += 1

    def colorat(self, x, y):
        if x > len(self.rowslist):
            raise IndexError("Row exceeds limit")
        elif y > (len(self.rowslist[0])):
            raise IndexError("Column exceeds limit")
        else:
            return self.rowslist[x][y]

    def __getitem__(self, index):
        x, y = index
        return self.colorat(x, y)

    def __setitem__(self, index, value):
        x, y = index
        if x > len(self.rowslist):
            raise IndexError("Row exceeds limit")
        elif y > (len(self.rowslist[0])):
            raise IndexError("Column exceeds limit")
        else:
            self.rowslist[x][y] = value

    def __iter__(self):
        return iter(self.rowslist.items())

    def __repr__(self):
        final_str = ""
        for each_row in self.rowslist:
            final_str += str(self.rowslist[each_row]) + '\n'
        return final_str


# Oh god, I pray to thee, forgive me, for, I never write such absolute dogwater as this very often
