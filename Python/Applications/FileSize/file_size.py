def file_sizes(filenames):
    output = {}

    for one_filename in filenames:
        try:
            size = 0
            with open(one_filename, 'r') as file:
                for one_line in file:
                    size += len(one_line)

            output[one_filename] = size
        except IOError:
            print(f"Could not read file: {one_filename}")
            output[one_filename] = None

    return output