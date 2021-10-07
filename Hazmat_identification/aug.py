import imageio as io
import pathlib
from os import listdir,mkdir
from os.path import isfile,exists,join
import imgaug.augmenters as ia
from imgaug.augmentables import BoundingBox, BoundingBoxesOnImage,batches
import xml.etree.ElementTree as ET


# Importar diretório das imagens e annotations do dataset:
dir = ['Hazmat Datasets','Hazmat annotation']

# Importar nome das labels:
clsid = {"Corrosive":0,"Dangerous when wet":1}

def get_boxes(xml):
    boxes = list()
    tree = ET.parse(xml)
    root = tree.getroot()
    for obj in root.iter("object"):
        cls = obj.find('name').text
        xmlbox = obj.find('bndbox')
        b = (float(xmlbox.find('xmin').text), float(xmlbox.find('xmax').text), float(xmlbox.find('ymin').text), float(xmlbox.find('ymax').text))
        box_data = BoundingBox(x1=b[0],y1=b[2],x2=b[1],y2=b[3],label=cls)
        boxes.append(box_data)
    return boxes

def get_size(xml):
    tree = ET.parse(xml)
    root = tree.getroot()
    size = root.find("size")
    w = int(size.find('width').text)
    h = int(size.find('height').text)
    size = [w,h]
    return size

def convert(xmin,xmax,ymin,ymax,size):
    dw = 1./(size[0])
    dh = 1./(size[1])
    x = (xmin + xmax)/2.0 - 1
    y = (ymin + ymax)/2.0 - 1
    w = xmax - xmin
    h = ymax - ymin
    x = x*dw
    w = w*dw
    y = y*dh
    h = h*dh
    return (x,y,w,h)

def convert_annotation(bbs,size):
    bimgs=list()
    for bb_imgs,size_img in (bbs,size):
        bimg = list()
        for bb in bb_imgs.items:
            xmin = bb.x1
            xmax = bb.x2
            ymin = bb.y1
            ymax = bb.y2
            cl = bb.label
            conv = convert(xmin,xmax,ymin,ymax,size_img)
            bimg.append([conv,cl])
        bimgs.append(bimg)
    return bimgs 


seq = ia.Sequential([
    ia.GaussianBlur(sigma=(0,4)),
    ia.Affine(rotate=(-25,25),scale=(0.8,1.2)),
    ia.MultiplyAndAddToBrightness(add=(-25,25))
],random_order=True)

for label_dir in listdir(dir[0]):
    img_names = [img for img in listdir(join(dir[0],label_dir))]
    img_list = [io.imread(img) for img in listdir(join(dir[0],label_dir))]
    xml_list = [xml for xml in listdir(join(dir[1],label_dir))]
    bbs_list = [BoundingBoxesOnImage(get_boxes(xml)) for xml in xml_list]
    size_list = [get_size(xml) for xml in xml_list]
    batch = batches.Batch(images=img_list,bounding_boxes=bbs_list)
    batch_aug = seq.augment_batch_(batch=batch)
    aug_imgs = batch_aug.images_aug
    path0 = join(dir[0],label_dir,"aug")
    path1 = join(dir[1],label_dir,'aug')
    path2 = join(path1,"obj_data")
    mkdir(path0)
    mkdir(path1)
    mkdir(path2)
    for img,name in (aug_imgs,img_names):
        io.imwrite(path0+'/'+name+".jpg",img)
    with open(path1+"/train.txt","w") as f1:
        for filepath in pathlib.Path(join(dir[0],label_dir)).glob("**/*"):
            f1.write(filepath.absolute() + "\n")
    bbs_aug = batch_aug.bounding_boxes_aug
    yolo = convert_annotation(bbs_aug,size_list)
    for bimg,name in (yolo,img_names):
        with open(path2+"/"+name+".txt","w") as f2:
            for b,cla in bimg:
                f2.write(("{0} {1} {2} {3} {4}".format(clsid[cla],b[0],b[1],b[2],b[3]))+"\n")
