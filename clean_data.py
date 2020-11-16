import pickle
import pandas as pd

full_data = pickle.load(open('flights_dataframe.pickle', 'rb'))

brief_data = pd.DataFrame(columns=['from', 'to', 'price'])
# from,to,price

for index, row in full_data.iterrows():
    origin = row['originAirportShortName']
    destination = row['airport']['shortName']
    price = row['flightInfo']['price']

    if price < 20000 and row['country']['code'] == 'US':
        brief_data = brief_data.append(
            {'from': origin, 'to': destination, 'price': price}, ignore_index=True)

# save to csv
brief_data.to_csv(path_or_buf='flights.csv', header=False, index=False)
