print("Loading AI\n")


ArtificialIntelligence = function(
EnemyHitStatus, RandomNumber, AnimationID, Ticks, CharGroundLevel, EnemyGroundLevel, 
CharCrouchPosition, EnemyCrouchPosition, Difficulty, CharHealth, EnemyHealth, CharacterTextureSizeDrawn,
DrawCharX, DrawEnemyX, CharDistanceX, CharDistanceY, EnemyAnimationType, CharSpecialEffectStage, EnemySpecialEffectStage,
CharWidth, EnemyWidth, CharacterName, RealCharDistanceX, CharNeedsMoreCounters
)


if EnemyHitStatus ~= 0 then return nil, nil, -2 end

--RandomNumber = RandomNumber%100
RandomNumber = 0

if RandomNumber > Difficulty and Ticks < 10 then
if CharGroundLevel == 1 then

if CharCrouchPosition ~= 0 then return nil, nil, -2 
else

if RandomNumber < Difficulty/2 then return nil, nil, 3
else return nil, nil, -2 end

end


else return nil, nil, -2 end

else

--RandomNumber = ((RandomNumber+Ticks)*10)%1000
RandomNumber = 0

if EnemyAnimationType == 3 or EnemyAnimationType == 6 or EnemyAnimationType == 8 then

if CharCrouchPosition ~= 0 then
if EnemyGroundLevel == 0 then return nil, nil, 10
else return nil, nil, 7 end

elseif CharGroundLevel == 0 then return 57, nil, nil
else

if EnemyCrouchPosition ~= 0 then

if CharDistanceX < (CharacterTextureSizeDrawn/2) then
--5
if(DrawCharX+CharacterTextureSizeDrawn > 640 or DrawCharX < 0) and CharNeedsMoreCounters.AirBeingHitCounter < 3 then return nil, nil, 5
--6
elseif CharHealth > EnemyHealth then return nil, nil, 6
elseif CharNeedsMoreCounters.CrouchBeingHitCounter < -3 then return 51, nil, nil
else return nil, nil, 9 end
--5
else return nil, nil, -2  end
--4

else return nil, nil, 8 end
--3
end
--2




elseif EnemyAnimationType == 7 or EnemySpecialEffectStage ~= 0 then
if CharGroundLevel == 1 then
--3
if CharCrouchPosition ~= 0 then return nil, nil, 7
--4
else return nil, nil, 8 end
--3
end

--2


elseif CharCrouchPosition ~= 0 then
if CharDistanceX > CharWidth then return nil, nil, 10
--3
--elseif CharNeedsMoreCounters.CrouchBeingHitCounter > 3 then
--3
--CharNeedsMoreCounters.CrouchBeingHitCounter = CharNeedsMoreCounters.CrouchBeingHitCounter-1
--return nil, nil, 10

elseif EnemyGroundLevel == 1 then return 49, nil, nil
else return 67, nil, nil end

--2


elseif CharGroundLevel == 0 then return 57, nil, nil

--2

elseif SpecialAllowed == 1 and RandomNumber <= 200 then

--2

if CharDistanceX <= 5 then return 59, nil, nil

--3

elseif CharDistanceX <= 15 then
if RandomNumber > 100 then return 61, nil, nil

--4

else return 63, nil, nil end

--3

elseif CharDistanceX > 15 then return 65, nil, nil end

--2

else
if CharDistanceX > CharWidth then return nil, nil, 2

--3

elseif CharNeedsMoreCounters.AirHitCounter > 3 and CharNeedsMoreCounters.AirBeingHitCounter < 3 then return nil, nil, 4
elseif EnemyCrouchPosition ~= 0 or CharNeedsMoreCounters.CrouchHitCounter > 3 and CharNeedsMoreCounters.CrouchBeingHitCounter < 3 then return nil, nil, 9
elseif CharDistanceX < CharWidth/2 then return 69, nil, nil
elseif EnemyGroundLevel == 0 then
if CharNeedsMoreCounters.GroundBeingHitCounter > CharNeedsMoreCounters.AirBeingHitCounter then return nil, nil, 4

--4

else return 55, nil, nil end

--3

else return 53, nil, nil end

--2

end

--1

end




return nil, nil, nil

end