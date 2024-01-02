#!/usr/bin/python3
"""REST API for employees' todo list"""

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

    with open('{}.csv'.format(employeeId), 'w') as file:
        for task in tasks:
            file.write('"{}","{}","{}","{}"\n'
                       .format(employeeId, username, task.get('completed'),
                               task.get('title')))
