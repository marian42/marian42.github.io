import jinja2

environment = jinja2.Environment(loader=jinja2.FileSystemLoader('theme/templates'))

page = environment.get_template('index.html')
article = environment.get_template('article.html')
image = environment.get_template('image.html')
video = environment.get_template('video.html')