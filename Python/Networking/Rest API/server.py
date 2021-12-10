
from flask import Flask, request, jsonify
from simple_websocket_server import WebSocketServer, WebSocket
from threading import Thread

from proton import Message
from proton.handlers import MessagingHandler
from proton.reactor import Container

app = Flask(__name__)

countries = [
    {"id": 1, "name": "Thailand", "capital": "Bangkok", "area": 513120},
    {"id": 2, "name": "Australia", "capital": "Canberra", "area": 7617930},
    {"id": 3, "name": "Egypt", "capital": "Cairo", "area": 1010408},
]

def _find_next_id():
    return max(country["id"] for country in countries) + 1

@app.get("/countries")    # endpoint
def get_countries():
    return jsonify(countries)

@app.post("/countries")
def add_country():
    if request.is_json:
        country = request.get_json()
        country["id"] = _find_next_id()
        countries.append(country)
        return country, 201
    return {"error": "Request must be JSON"}, 415

class SimpleEcho(WebSocket):
    def handle(self):
        # echo message back to client
        self.send_message("server: " + self.data)

    def connected(self):
        print(self.address, 'connected')

    def handle_close(self):
        print(self.address, 'closed')

class IntercomHandler(MessagingHandler):
    def __init__(self):
        # super(IntercomHandler, self).__init__()
        super().__init__()
        self.url = "localhost:5672"
        self.rcv_queue = "admin_interface_daemon"
        self.send_queue = "intercom_daemon"
        self.broadcast_topic = ""

    def on_start(self, event):
        """Asynchronous start Method which creates the AMQP receiver."""
        """Method to create connection to broker and
        create sender and receiver channel."""

        print("on_start")
        event.container.create_receiver("localhost:5672/admin_interface_daemon")
        # connection = event.container.connect(url=self.url)
        # if connection:
        #     print("connecting: " + self.rcv_queue)
        #     event.container.create_receiver(connection, source=self.rcv_queue)
        #     self.sender = event.container.create_sender(
        #         connection, target=self.send_queue
        #     )
        # else:
        #     print("Unable to establish connection to broker!")

    def on_message(self, event):
        print("message received: " + event.message.body)


if __name__ == '__main__':
    # server = WebSocketServer('', 8081, SimpleEcho)
    # websocket_thread = Thread(target=server.serve_forever)
    # websocket_thread.start()

    handler = IntercomHandler()
    # message_thread = Thread(target=Container(handler).run)
    # message_thread.start()
    Container(handler).run()

    # app.run(host="localhost", port=8080)