import sqlite3
import random
print("Hello World")
# Open the stock.db file
conn = sqlite3.connect('stock.db')
cursor = conn.cursor()
price=50
# Loop to execute the INSERT statement
for timestamp in range(1001,10001,1):
    symbol = "100001"
    price = price*(1+random.uniform(-0.01, 0.01))
    cursor.execute("INSERT INTO stock_prices (symbol, price, timestamp) VALUES (?, ?, ?)", (symbol, price, timestamp))

# Commit the changes
conn.commit()

# Close the connection
conn.close()