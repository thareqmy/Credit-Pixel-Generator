import xlrd
book = xlrd.open_workbook("pixel.xls", formatting_info=True)
sheets = book.sheet_names()
print("sheets are:", sheets)
for index, sh in enumerate(sheets):
    sheet = book.sheet_by_index(index)
    print("Sheet:", sheet.name)
    rows, cols = sheet.nrows, sheet.ncols
    with open("Alphabet/{}.txt".format(sheet.name), 'w') as f:

        #print("Number of rows: %s   Number of cols: %s" % (rows, cols))
        for row in range(rows):
            for col in range(cols):
                #print("row, col is:", row+1, col+1)
                thecell = sheet.cell(row, col)      
                # could get 'dump', 'value', 'xf_index'
                xfx = sheet.cell_xf_index(row, col)
                xf = book.xf_list[xfx]
                bgx = xf.background.pattern_colour_index
                if (bgx == 8):
                    f.write(thecell.value)
                    f.write('\n')