import argparse,os,imageio
import imgaug.augmenters as ia

parser = argparse.ArgumentParser()

def parse():
    print("\n")
    print("--------------- Sérginho Augmentations ---------------")
    print("\n")
    parser.add_argument("--img_dir",help="The path to the images",required=True)
    parser.add_argument("--xml_dir",help="The path to the xml folder",required=False)
    parser.add_argument("--out",help="The path to the output",required=True)
    parser.add_argument("--mult",help="The number of copies for each picture",required=False,type=int)
    return parser.parse_args()
    
args = parse()

seq = ia.Sequential([
    ia.GaussianBlur(sigma=(0,4)),
    ia.Affine(rotate=(-25,25),scale=(0.8,1.2)),
    ia.MultiplyAndAddToBrightness(add=(-25,25))
],random_order=True)

if args.mult == None:
    for el in os.listdir(args.img_dir):
        image = imageio.imread(args.img_dir + ("/{0}".format(el)))
        img_aug = seq(image=image)
        imageio.imwrite(args.out+"/"+el+"_aug.jpg",img_aug)

else:
    batch = list()
    for el in os.listdir(args.img_dir):
        for i in range(args.mult):
            image = imageio.imread(args.img_dir + ("/{0}".format(el)))
            batch.append(image)
    img_aug = seq(images=batch)
    for i in range(len(img_aug)):
        imageio.imwrite(args.out+"/"+el+("_aug{0}.jpg".format(i)),img_aug[i])
        
print('Processo realizado com sucesso')