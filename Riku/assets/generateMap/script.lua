asset_type="map_generator"

map_generator = {}

function squareDiamondSizeTmp(var)
	ret=3
	while ret<var do
		ret=2*ret-1
	end
	return ret
end

function my_rand(middle, spread)
	return (math.random()-0.5)*spread+middle
end


--function takes size (x,y), begin_value (4 corners)
function squareDiamond(sx,sy, height_diff, min_height, max_height)
	local size = squareDiamondSizeTmp(math.max(sx,sy))
	local heights = {}
	--init height array
	for i=1,size do
		heights[i]={}
		for j=1,size do
			heights[i][j]=0.0
		end
	end
	--init values
	heights[1][1]=my_rand(4.0,8.0)
	heights[1][size]=my_rand(4.0,8.0)
	heights[size][1]=my_rand(4.0,8.0)
	heights[size][size]=my_rand(4.0,8.0)
	diff=size-1
	--main square dimaond
	while diff>=2 do
		--diamond
		for x=1,size-diff, diff do
			for y=1, size-diff, diff do
				--diamond
				avg=(heights[x][y]+heights[x+diff][y]+heights[x][y+diff]+heights[x+diff][y+diff])/4.0
				heights[x+diff/2][y+diff/2]=my_rand(avg, height_diff*diff*1.4142)
			end
		end
		--square
		for x=1, size, diff/2 do
			for y=1+(x+diff/2-1)%diff, size, diff do
				count=0
				avg=0
				if (x+diff/2<=size) then
					avg=avg+heights[x+diff/2][y]
					count=count+1
				end
				if (x-diff/2>0) then
					avg=avg+heights[x-diff/2][y]
					count=count+1
				end
				if (y+diff/2<=size) then
					avg=avg+heights[x][y+diff/2]
					count=count+1
				end
				if (y-diff/2>0) then
					avg=avg+heights[x][y-diff/2]
					count=count+1
				end
				heights[x][y] = my_rand(avg/count, height_diff*diff)
			end
		end
		diff=diff/2
	end
	--normalizing heights
	if(x==1 and y==1) then
		return heights
	end
	--find max and min
	h_min = heights[1][1]
	h_max = heights[1][1]
	for i=1,size do
		for j=1,size do
			if(heights[i][j]>h_max) then
				h_max=heights[i][j]
			end
			if(heights[i][j]<h_min) then
				h_min=heights[i][j]
			end
		end
	end
	--scale height
	if(h_max-h_min>0.0000001) then
		for i=1,size do
			for j=1,size do
				heights[i][j]=min_height+(heights[i][j]-h_min)*(max_height-min_height)/(h_max-h_min)
			end
		end
	else
		for i=1,size do
			for j=1,size do
				heights[i][j]=(min_height+max_height)/2
			end
		end
	
	end
	return heights
end


function setTemperatures(x, y, heights, T_m, T_d, T_h)
	--T_m - temperature in center of map for height=0
	--T_d - temperature reduce (when going to lesser y for northern hemisphere)
	--T_h - temperature reduce for height difference=1
	local Temp_tile=T_d/math.max(1,y-1)
	local temperatures = {}
	for i=1,x do
		temperatures[i] = {}
		for j=1,y do
			temperatures[i][j]=T_m+Temp_tile*((j-1)-((y-1)/2))-T_h*math.max(heights[i][j],0.0)
		end
	end
	return temperatures
end


function setDryness(x, y, heights, D)
	 local dryness = {}
	 --init values
	 for i=1,x do
	 	dryness[i]={}
	 	for j=1,y do
	 		if(heights[i][j]<-0.5) then
	 			dryness[i][j]=0.0
	 		else
	 			dryness[i][j]=100000000.0
	 		end
	 	end
	 end
	 --main loop
	 for val=0,5*(x+y),1 do
	 	for i=1,x do
	 		for j=1,y do
	 			if(dryness[i][j]==val) then
	 				--diagonal
	 				if(i>1 and j>1 and dryness[i-1][j-1]>dryness[i][j]+7) then
	 					dryness[i][j]=dryness[i-1][j-1]+7
	 				end
	 				if(i>1 and j<y and dryness[i-1][j+1]>dryness[i][j]+7) then
	 					dryness[i][j]=dryness[i-1][j+1]+7
	 				end
	 				if(i<x and j>1 and dryness[i+1][j-1]>dryness[i][j]+7) then
	 					dryness[i][j]=dryness[i+1][j-1]+7
	 				end
	 				if(i<x and j<y and dryness[i+1][j+1]>dryness[i][j]+7) then
	 					dryness[i][j]=dryness[i+1][j+1]+7
	 				end
	 				--side
	 				if(i>1 and dryness[i-1][j]>dryness[i][j]+5) then
	 					dryness[i][j]=dryness[i-1][j]+5
	 				end
	 				if(i<x and dryness[i+1][j]>dryness[i][j]+5) then
	 					dryness[i][j]=dryness[i+1][j]+5
	 				end
	 				if(j>1 and dryness[i][j-1]>dryness[i][j]+5) then
	 					dryness[i][j]=dryness[i][j-1]+5
	 				end
	 				if(j<y and dryness[i][j+1]>dryness[i][j]+5) then
	 					dryness[i][j]=dryness[i][j+1]+5
	 				end
	 			end
	 		end
	 	end
	 end
	 --scale
	 for i=1,x do
	 	for j=1,y do
	 		dryness[i][j]=dryness[i][j]*D/(5*(x+y)/2)
	 	end
	 end
	 return dryness
end


function getBiomeIndex(temp, rand_fact)
	local biomeMins = {0.00, 0.20, 0.40, 0.70, 1.00}
	temp=temp+math.random()*rand_fact*2.0-rand_fact
	local i=1
	while i<6 and biomeMins[i]<=temp do
		i=i+1
	end
	return i
end


function getDryIndex(dry, rand_fact)
	local biomeMins = {0.50, 1.00}
	dry=dry+math.random()*rand_fact*2.0-rand_fact
	local i=1
	while i<3 and biomeMins[i]<=dry do
		i=i+1
	end
	return i
end


function onCreateMap()
	local x=20
	local y=20
	local arr = {}
	local biomes = {"snow","tundra","taiga","temperate","mediterranean","tropics","sea"}
	local grounds = {"snow", "stone", "tundra", "grass_taiga", "hot_desert","grass","snow", "grass_tropics", "cold_desert", "semihot_desert"}
	local areas = {"wet","dry"}
	math.randomseed(os.time())
	local heights = squareDiamond(x,y, 0.20, 0.0, 6.0)
	local temperatures = setTemperatures(x,y,heights,0.90,0.40,0.20)
	local dryness = setDryness(x,y,heights,2.40)

	--there would be added +/-0.05 factor
	
	for i=1,x do
		arr[i]={}
		for j=1,y do
			--piąty parametr to obiekt na mapie
			if(heights[i][j]<-0.5) then
				arr[i][j] = TileDescription.new(0,"sea","water",areas[math.random(2)],"")
			else
				biomeInd = getBiomeIndex(temperatures[i][j],0.05)
				dryInd = getDryIndex(dryness[i][j],0.05)
				if(biomeInd==1) then
					arr[i][j] = TileDescription.new(math.floor(heights[i][j]+0.5),biomes[biomeInd],grounds[math.random(2)],areas[math.random(2)], "")
				elseif (biomeInd<3) then --tundra or taiga
					arr[i][j] = TileDescription.new(math.floor(heights[i][j]+0.5),biomes[biomeInd],grounds[1+biomeInd],areas[math.random(2)],"taiga_tree")
				elseif (biomeInd==4) then
					if (dryInd==1) then--forest
						arr[i][j] = TileDescription.new(math.floor(heights[i][j]+0.5),biomes[biomeInd],grounds[6],areas[math.random(2)],"tree")
					elseif (dryInd==2) then--steppe
						arr[i][j] = TileDescription.new(math.floor(heights[i][j]+0.5),biomes[biomeInd],grounds[6],areas[math.random(2)], "")
					else --desert
						arr[i][j] = TileDescription.new(math.floor(heights[i][j]+0.5),biomes[biomeInd],"cold_desert","dry", "")
					end
				elseif (biomeInd==5) then --mediterranean
					if (dryInd==1) then--forest
						arr[i][j] = TileDescription.new(math.floor(heights[i][j]+0.5),biomes[5],grounds[6],areas[math.random(2)],"tree")
					else--desert
						arr[i][j] = TileDescription.new(math.floor(heights[i][j]+0.5),biomes[5],"semihot_desert","dry", "")
					end
				else --tropics
					if (dryInd==1) then--forest
						arr[i][j] = TileDescription.new(math.floor(heights[i][j]+0.5),biomes[6],"grass_tropics",areas[math.random(2)],"")
					else--desert
							arr[i][j] = TileDescription.new(math.floor(heights[i][j]+0.5),biomes[6],"hot_desert","dry", "")
					end
				end
			end
		end
	end
	return arr
end

