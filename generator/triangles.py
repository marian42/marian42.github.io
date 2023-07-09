import math
import random

random.seed(0)

TRIANGLE_SIZE = 20
HEIGHT = (TRIANGLE_SIZE * math.sqrt(3)) / 2

GROWTH = TRIANGLE_SIZE / 2
ANGLE_RAD = math.radians(30)
GROWTH_X = math.cos(ANGLE_RAD) * GROWTH
GROWTH_Y = math.sin(ANGLE_RAD) * GROWTH

def get_triangle_overlapping(index_x, index_y):
    if index_x % 2 != 0:
        index_y += 1
    if index_y % 2 != 0:
        return [
            (index_x * HEIGHT, (index_y // 2 - index_x % 2 * 0.5) * TRIANGLE_SIZE),
            (index_x * HEIGHT, (index_y // 2 + 1 - index_x % 2 * 0.5) * TRIANGLE_SIZE),
            (index_x * HEIGHT + GROWTH, (index_y // 2 + 1 - index_x % 2 * 0.5) * TRIANGLE_SIZE + GROWTH),
            ((index_x + 1) * HEIGHT + GROWTH_X, (index_y // 2 + 0.5 - index_x % 2 * 0.5) * TRIANGLE_SIZE + GROWTH_Y)
        ]
    else:
        return [
            ((index_x + 1) * HEIGHT + GROWTH_X, (index_y // 2 - 0.5 - index_x % 2 * 0.5) * TRIANGLE_SIZE - GROWTH_Y),
            (index_x * HEIGHT, (index_y // 2 - index_x % 2 * 0.5) * TRIANGLE_SIZE),
            (index_x * HEIGHT + GROWTH, (index_y // 2 - index_x % 2 * 0.5) * TRIANGLE_SIZE + GROWTH),
            ((index_x + 1) * HEIGHT + GROWTH_X, (index_y // 2 + 0.5 - index_x % 2 * 0.5) * TRIANGLE_SIZE + GROWTH_Y)
        ]
    

def get_triangle(index_x, index_y):
    if index_x % 2 != 0:
        index_y += 1
    if index_y % 2 != 0:
        return [
            (index_x * HEIGHT, (index_y // 2 - index_x % 2 * 0.5) * TRIANGLE_SIZE),
            (index_x * HEIGHT, (index_y // 2 + 1 - index_x % 2 * 0.5) * TRIANGLE_SIZE),
            ((index_x + 1) * HEIGHT, (index_y // 2 + 0.5 - index_x % 2 * 0.5) * TRIANGLE_SIZE)
        ]
    else:
        return [
            ((index_x + 1) * HEIGHT, (index_y // 2 - 0.5 - index_x % 2 * 0.5) * TRIANGLE_SIZE),
            (index_x * HEIGHT, (index_y // 2 - index_x % 2 * 0.5) * TRIANGLE_SIZE),
            ((index_x + 1) * HEIGHT, (index_y // 2 + 0.5 - index_x % 2 * 0.5) * TRIANGLE_SIZE),
        ]
    
def get_random_colour():
    RANGE = 0.1
    brightness = random.random() * RANGE + 0.02
    value = int(brightness * 255)
    return '#' + "{0:02x}".format(value) * 3

def format_number(number):
    if abs(round(number) - number) < 0.005:
        return str(int(number))

    return '{:.1f}'.format(number)
    
def get_svg_triangle(x, y, color=None, overlap=True):
    vertices = get_triangle_overlapping(x, y) if overlap else get_triangle(x, y)
    result = '\t<polygon points="'
    result += ' '.join(format_number(vert[0]) + ',' + format_number(vert[1]) for vert in vertices)
    if color is None:
        color = get_random_colour()
    result += '" fill="' + color + '"/>'
    return result

def get_svg_polygon(vertices, color=None):
    result = '\t<polygon points="'
    result += ' '.join(format_number(vert[0]) + ',' + format_number(vert[1]) for vert in vertices)
    if color is None:
        color = get_random_colour()
    result += '" fill="' + color + '"/>'
    return result

LIGHT = [
    (1, 4), (1, 5), (1, 6), (1, 7), #M
    (6, 5), (6, 6), (6, 7), #A
    (11, 4), (11, 5), (11, 6), (11, 7), #R
    (15, 4), (15, 5), (15, 6), (15, 7), #I
    (18, 5), (18, 6), (18, 7), #A
    (23, 4), (23, 5), (23, 6), (23, 7), #N
    ]
MED = [
    (1, 3), (2, 3), (2, 4), (3, 3), (3, 4), (4, 3), #M
    (6, 4), (7, 3), (7, 4), (7, 6), (8, 3), (8, 4), (8, 6), (9, 4), #A
    (11, 3), (12, 3), (12, 4), (12, 6), (13, 4), (13, 6), #R
    (15, 3), (16, 3), #I
    (18, 4), (19, 3), (19, 4), (19, 6), (20, 3), (20, 4), (20, 6), (21, 4), #A
    (23, 3), (24, 3), (24, 4), (25, 4), (25, 5), (26, 5) #N
    ]
DARK = [
    (4, 4), (4, 5), (4, 6), (4, 7), #M
    (9, 5), (9, 6), (9, 7), #A
    (13, 7), #R
    (16, 4), (16, 5), (16, 6), (16, 7), #I
    (21, 5), (21, 6), (21, 7), #A
    (26, 3), (26, 4), (26, 6), (26, 7) #N
    ]


COLORS = ['#E0E0E0', '#C4C4C4', '#A5A5A5']

def clean_point(point):
    rounding_factor = 4
    return (round(point[0] * rounding_factor) / rounding_factor, round(point[1] * rounding_factor) / rounding_factor)

def follow_edge(point, edges):
    for p1, p2 in edges:
        if point == p1:
            return p2

def merge_triangles(triangles):
    triangles = [[clean_point(point) for point in triangle] for triangle in triangles]

    edges = set()
    for triangle in triangles:
        edges.add((triangle[0], triangle[1]))
        edges.add((triangle[1], triangle[2]))
        edges.add((triangle[2], triangle[0]))

    outer_edges = set()
    for p1, p2 in edges:
        if (p2, p1) not in edges:
            outer_edges.add((p1, p2))
    
    polygons = []
    while any(outer_edges):
        polygon = []
        start = next(iter(outer_edges))[0]
        polygon = [start]
        point = follow_edge(start, outer_edges)
        outer_edges.remove((start, point))
        while point != start:
            polygon.append(point)
            point2 = follow_edge(point, outer_edges)
            outer_edges.remove((point, point2))
            point = point2

        polygons.append(polygon)

    return polygons    

def save_file(lines, width, height, filename):
    content = '<svg width="' + str(width) + '" height="' + str(height) + '" xmlns="http://www.w3.org/2000/svg">\n'
    content += '\n'.join(lines)
    content += '\n</svg>'

    with open(filename, 'w') as file:
        file.write(content)

def create_triangles(horizontal_triangles=12, vertical_triangles=11):
    lines = []
    for x in range(horizontal_triangles):
        for y in range(vertical_triangles):
            lines.append(get_svg_triangle(x, y))

    save_file(lines, horizontal_triangles * HEIGHT, (vertical_triangles / 2 - 0.5) * TRIANGLE_SIZE, 'theme/triangles.svg')

def get_neighbors(x, y):
    return (
        (x, y - 1),
        (x, y + 1),
        (x - 1, y) if y % 2 != x % 2 else (x + 1, y))

def create_logo():
    LOGO_HORIZONTAL_TRIANGLES = 28
    LOGO_VERTICAL_TRIANGLES = 11

    lines = []

    # LIGHT
    triangles = []
    
    for x in range(LOGO_HORIZONTAL_TRIANGLES):
        for y in range(LOGO_VERTICAL_TRIANGLES):
            if (x, y) in LIGHT:
                triangles.append(get_triangle(x, y))
                for neighbor in get_neighbors(x, y):
                    if neighbor in MED or neighbor in DARK:
                        triangles.append(get_triangle(*neighbor))

    polygons = merge_triangles(triangles)
    for polygon in polygons:
        lines.append(get_svg_polygon(polygon, COLORS[0]))

    # MED
    triangles = []
    for x in range(LOGO_HORIZONTAL_TRIANGLES):
        for y in range(LOGO_VERTICAL_TRIANGLES):
            if (x, y) in MED:
                triangles.append(get_triangle(x, y))
                for neighbor in get_neighbors(x, y):
                    if neighbor in DARK:
                        triangles.append(get_triangle(*neighbor))

    polygons = merge_triangles(triangles)
    for polygon in polygons:
        lines.append(get_svg_polygon(polygon, COLORS[1]))

    # DARK
    triangles = []
    for x in range(LOGO_HORIZONTAL_TRIANGLES):
        for y in range(LOGO_VERTICAL_TRIANGLES):
            if (x, y) in DARK:
                triangles.append(get_triangle(x, y))

    polygons = merge_triangles(triangles)
    for polygon in polygons:
        lines.append(get_svg_polygon(polygon, COLORS[2]))

    save_file(lines, LOGO_HORIZONTAL_TRIANGLES * HEIGHT, (LOGO_VERTICAL_TRIANGLES / 2 - 0.5) * TRIANGLE_SIZE, 'theme/logo.svg')
    

create_triangles()
create_logo()