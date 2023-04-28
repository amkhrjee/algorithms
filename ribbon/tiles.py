from Tile import Tile

# Y --> Yellow
# W --> White
# G --> Green
# B --> Blue
# O --> Orange

tile_list = [
    Tile(2, ['O', 'Y', 'W', 'Y']),
    Tile(2, ['G', 'W', 'Y', 'G', 'O', 'G']),
    Tile(2, ['G', 'O', 'B', 'O']),
    Tile(3, ['O', 'Y', 'O', 'Y', 'W', 'Y']),
    Tile(3, ['W', 'B', 'R', 'G', 'O', 'G']),
    Tile(1, ['R', 'G', 'W']),
]

# The following algorithm assumes that reorientation of the tiles is *not* allowed

# we need to check both row-wise and col-wise


def get_complete_tile(tile_list):
    for each_tile in tile_list:
        for another_tile in tile_list[tile_list.index(each_tile) + 1:]:
            rows_to_check = min(each_tile.rows, another_tile.rows)
            cols_to_check = min(each_tile.cols, another_tile.cols)
            if each_tile.rows == another_tile.rows:
                index = 0
                while index in range(cols_to_check):
                    # if each_tile.colslist[index] == another_tile.colslist[index]:
                        
                    # index += 1

# for each_tile in tile_list:
#     print(each_tile.colslist)

# get_complete_tile(tile_list)