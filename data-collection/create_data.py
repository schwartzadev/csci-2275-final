import pdb
from numpy.core.numeric import full
import requests
import json
import pandas as pd
import pickle

params = {
    'airport': 'DEN',
    'flightMaxStops': '0',
    'stopsFilterActive': 'true',
    'zoomLevel': '4',
    'selectedDestination': '',
}

airports = ["ATL", "LAX", "ORD", "DFW", "DEN", "JFK", "SFO", "SEA", "LAS", "MCO", "EWR", "CLT", "PHX", "IAH",
            "MIA", "BOS", "MSP", "FLL", "DTW", "PHL", "LGA", "BWI", "SLC", "SAN", "IAD", "DCA", "MDW", "TPA", "PDX", "HNL", "BNA", "AUS", "DAL", "STL", "SJC", "HOU", "OAK", "MSY", "RDU", "SMF", "MCI", "SNA", "SAT", "CLE", "RSW", "IND", "PIT", "SJU", "CVG", "CMH", "OGG", "MKE", "BDL", "PBI", "JAX", "BUR", "ABQ", "ANC", "BUF", "ONT", "OMA"]

full_data = pd.DataFrame()
for airport in airports:
    params['airport'] = airport
    response = requests.get(
        'https://www.kayak.com/s/horizon/exploreapi/destinations', params=params)
    data = json.loads(response.content)

    if airport == airports[0]:
        # first airport: create dataframe
        full_data = pd.DataFrame(data['destinations'])
    else:
        # all others: append dataframe
        new_data = pd.DataFrame(data['destinations'])
        full_data = full_data.append(new_data, ignore_index=True)

with open('flights_dataframe.pickle', 'wb') as handle:
    pickle.dump(full_data, handle)

import pdb; pdb.set_trace()
