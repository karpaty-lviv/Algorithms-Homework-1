import pandas as pd
import matplotlib.pyplot as plt
import os

CSV_FILE = './data/results.csv'
OUTPUT_DIR = './data/graphs'

if not os.path.exists(OUTPUT_DIR):
    os.makedirs(OUTPUT_DIR)

try:
    data = pd.read_csv(CSV_FILE)
except FileNotFoundError:
    print(f"Error file {CSV_FILE} not found.")
    exit()

variants = data['Variant'].unique()

print(f"Find variants: {', '.join(variants)}")

def create_plot(y_column, y_label, title, filename):
    """Creating plots"""
    plt.figure(figsize=(10, 6))
    
    for variant in variants:
        variant_data = data[data['Variant'] == variant]
        plt.plot(variant_data['Size'], variant_data[y_column], 
                 marker='o', linestyle='-', label=variant)

    plt.xlabel("Students number")
    plt.ylabel(y_label)
    plt.title(title)
    
    plt.xscale('log')
    plt.yscale('log')
    
    plt.legend()
    plt.grid(True, which="both", ls="--")

    output_path = os.path.join(OUTPUT_DIR, filename)
    plt.savefig(output_path)
    print(f"Plots are saved to: {output_path}")
    plt.close()


create_plot(
    y_column='TotalOperations',
    y_label='Operations in 10 seconds',
    title='Productivity comprasion',
    filename='1_total_operations.png'
)

create_plot(
    y_column='Memory',
    y_label='Memory usage (in bytes)',
    title='Memory usage comprassion',
    filename='2_memory_usage.png'
)

create_plot(
    y_column='OpsB_UpdateGroup',
    y_label='updateGroup operations in 10 seconds',
    title='updateGroup productivity',
    filename='3_ops_b_details.png'
)
