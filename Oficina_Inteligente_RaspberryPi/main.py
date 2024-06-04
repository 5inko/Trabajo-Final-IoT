# main.py
from kivy.app import App
from kivy.uix.label import Label
from kivy.uix.button import Button
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.slider import Slider
from coap_client import send_coap_message
from threading import Thread 

class LightsApp(App):

    def build(self):
        self.current_color = 'off'  # Para rastrear el color actual
        self.intensity = 255  # Intensidad inicial

        layout = BoxLayout(orientation='vertical')

        self.label = Label(text='Control de Luces')
        layout.add_widget(self.label)

        self.red_button = Button(text='Rojo')
        self.red_button.bind(on_press=self.set_red)
        layout.add_widget(self.red_button)

        self.red_slider = Slider(min=0, max=255, value=255)
        self.red_slider.bind(value=self.on_red_value)
        layout.add_widget(self.red_slider)

        self.blue_button = Button(text='Azul')
        self.blue_button.bind(on_press=self.set_blue)
        layout.add_widget(self.blue_button)

        self.blue_slider = Slider(min=0, max=255, value=255)
        self.blue_slider.bind(value=self.on_blue_value)
        layout.add_widget(self.blue_slider)

        self.green_button = Button(text='Verde')
        self.green_button.bind(on_press=self.set_green)
        layout.add_widget(self.green_button)

        self.green_slider = Slider(min=0, max=255, value=255)
        self.green_slider.bind(value=self.on_green_value)
        layout.add_widget(self.green_slider)

        self.off_button = Button(text='Apagar')
        self.off_button.bind(on_press=self.turn_off)
        layout.add_widget(self.off_button)

        return layout

    def send_coap_command(self, command, intensity=None):
        if intensity is None:
            intensity = self.intensity
        Thread(target=send_coap_message, args=(command, intensity)).start()  # Crear nueov hilo por proceso ejecutado

    def set_red(self, instance):
        self.current_color = 'red'
        self.intensity = self.red_slider.value  # Actualiza la intensidad
        self.send_coap_command(self.current_color)
        self.label.text = 'Luz Roja Encendida'

    def on_red_value(self, instance, value):
        if self.current_color == 'red':
            self.intensity = int(value)
            self.send_coap_command(self.current_color, self.intensity)

    def set_blue(self, instance):
        self.current_color = 'blue'
        self.intensity = self.blue_slider.value  # Actualiza la intensidad
        self.send_coap_command(self.current_color)
        self.label.text = 'Luz Azul Encendida'

    def on_blue_value(self, instance, value):
        if self.current_color == 'blue':
            self.intensity = int(value)
            self.send_coap_command(self.current_color, self.intensity)

    def set_green(self, instance):
        self.current_color = 'green'
        self.intensity = self.green_slider.value  # Actualiza la intensidad
        self.send_coap_command(self.current_color)
        self.label.text = 'Luz Verde Encendida'

    def on_green_value(self, instance, value):
        if self.current_color == 'green':
            self.intensity = int(value)
            self.send_coap_command(self.current_color, self.intensity)

    def turn_off(self, instance):
        self.current_color = 'off'
        self.send_coap_command(self.current_color)
        self.label.text = 'Luz Apagada'

if __name__ == '__main__':
    LightsApp().run()