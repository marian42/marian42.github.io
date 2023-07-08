import shutil
import os
from PIL import Image

from config import OUTPUT_DIRECTORY, IMAGE_WIDTH, FAST

# Class for images and videos
class Media:
    def __init__(self, article, base_url):
        self.base_url = base_url
        self.article = article
        self.source_file_path = os.path.join(self.article.directory, base_url)

        self.is_remote = False
        self.is_video = base_url.endswith('.mp4') or base_url.endswith('.webm') or base_url.endswith('.ogv')

        if not os.path.isfile(self.source_file_path):
            self.is_remote = True
            return

        full_size_path = os.path.join(OUTPUT_DIRECTORY, self.article.url[1:], base_url)
        target_directory = os.path.dirname(full_size_path)
        if not os.path.isdir(target_directory):
            os.makedirs(target_directory)

        if not FAST or not os.path.isfile(full_size_path):
            shutil.copy(self.source_file_path, full_size_path)

        if self.is_video:
            self.is_small = True
            return
            
        filename, file_extension = os.path.splitext(base_url)
        self.small_image_name = filename + "_" + str(IMAGE_WIDTH) + file_extension
        small_image_path = os.path.join(OUTPUT_DIRECTORY, self.article.url[1:], self.small_image_name)

        self.is_small = False
        if FAST and os.path.isfile(small_image_path):
            return

        image = Image.open(self.source_file_path)
        width, height = image.size

        if width <= IMAGE_WIDTH:
            self.is_small = True
        else:
            new_height = int(height * IMAGE_WIDTH / width)
            resized_image = image.resize((IMAGE_WIDTH, new_height))
            resized_image.save(small_image_path)

    def get_source(self, relative):
        if self.is_remote:
            return self.base_url
        
        filename = self.base_url if self.is_small else self.small_image_name

        if relative:
            return filename
        else:
            return self.article.url + filename        
    
    def get_link(self, relative):
        if self.is_remote:
            return self.base_url
        
        if relative:
            return self.base_url
        else:
            return self.article.url + self.base_url
   
media_cache = dict()

def get_media_from_cache(article, filename):
    global media_cache

    key = (article.slug, filename)
    if key in media_cache:
        return media_cache[key]
    else:
        item = Media(article, filename)
        media_cache[key] = item
        return item