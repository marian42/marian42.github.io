import jinja2

environment = jinja2.Environment(loader=jinja2.FileSystemLoader('theme/templates'))

page = environment.get_template('index.html')
article = environment.get_template('article.html')
article_summary = environment.get_template('article_summary.html')
image = environment.get_template('image.html')
video = environment.get_template('video.html')
youtube_embed = environment.get_template('youtube_embed.html')
redirect = environment.get_template('redirect.html')