import sqlite3
import csv
import os

def export_tables_to_csv(db_path, output_dir):
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    conn = sqlite3.connect(db_path)
    cursor = conn.cursor()

    cursor.execute("SELECT name FROM sqlite_master WHERE type='table';")
    tables = cursor.fetchall()

    for table_name in tables:
        table_name = table_name[0]
        output_path = os.path.join(output_dir, f"{table_name}.csv")
        
        with open(output_path, 'w', newline='', encoding='utf-8') as csv_file:
            csv_writer = csv.writer(csv_file)
            
            cursor.execute(f"PRAGMA table_info({table_name})")
            headers = [description[1] for description in cursor.fetchall()]
            csv_writer.writerow(headers)
            
            cursor.execute(f"SELECT * FROM {table_name}")
            rows = cursor.fetchall()
            csv_writer.writerows(rows)

    conn.close()

if __name__ == "__main__":
    export_tables_to_csv('in.db', 'out')