#!/usr/bin/python3
"""REST API for employees' todo list"""

import json
import requests
import sys


if __name__ == '__main__':
    employeeID = sys.argv[1]
    bUrl = "https://jsonplaceholder.typicode.com/users"
    url = bUrl + "/" + employeeID

    response = requests.get(url)
    username = response.json().get('username')

    todoUrl = url + "/todos"
    response = requests.get(todoUrl)
    tasks = response.json()

    dictionary = {employeeID: []}
    for task in tasks:
        dictionary[employeeID].append({
            "task": task.get('title'),
            "completed": task.get('completed'),
            "username": username
        })
    with open('{}.json'.format(employeeID), 'w') as filename:
        json.dump(dictionary, filename)
