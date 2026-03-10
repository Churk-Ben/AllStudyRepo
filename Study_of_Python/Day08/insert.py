import os
import csv

def create_insert_scripts(input_dir, output_dir):
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    for filename in os.listdir(input_dir):
        if filename.endswith('.csv'):
            table_name = os.path.splitext(filename)[0]
            sql_file_path = os.path.join(output_dir, f'{table_name}.sql')

            with open(os.path.join(input_dir, filename), 'r', encoding='utf-8') as csv_file:
                with open(sql_file_path, 'w', encoding='utf-8') as sql_file:
                    reader = csv.reader(csv_file)
                    try:
                        headers = next(reader)
                    except StopIteration:
                        continue  # Skip empty files

                    for row in reader:
                        processed_values = []
                        for val in row:
                            if val is None or val == '':
                                processed_values.append("NULL")
                            else:
                                escaped_val = str(val).replace("'", "''")
                                processed_values.append(f"'{escaped_val}'")

                        values_str = ', '.join(processed_values)
                        headers_str = ', '.join(f"`{h}`" for h in headers)
                        sql_statement = f"INSERT INTO `{table_name}` ({headers_str}) VALUES ({values_str});\n"
                        sql_file.write(sql_statement)

if __name__ == "__main__":
    create_insert_scripts('out', 'sql_inserts')