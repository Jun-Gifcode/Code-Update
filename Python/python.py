import sys


tokens = sys.stdin.read().split()
record_count = int(tokens[0])
patients = {}
token_index = 1

for _ in range(record_count):
	patient_id = tokens[token_index]
	room_number = int(tokens[token_index + 1])
	token_index += 2

	if len(patient_id) < 3 or not patient_id.isalnum() or not 1 <= room_number <= 9999:
		continue

	normalized_id = patient_id.upper()
	patient = patients.get(normalized_id)
	if patient is None:
		patients[normalized_id] = {
			"current_room": room_number,
			"highest_room": room_number,
			"transfer_count": 1,
			"unique_rooms": {room_number},
		}
	else:
		patient["current_room"] = room_number
		patient["highest_room"] = max(patient["highest_room"], room_number)
		patient["transfer_count"] += 1
		patient["unique_rooms"].add(room_number)

query_patient_id = tokens[token_index].upper()
patient = patients.get(query_patient_id)

if patient is None:
	print("NOT_FOUND")
else:
	unique_room_count = len(patient["unique_rooms"])
	priority_score = (
		patient["current_room"]
		+ patient["highest_room"]
		+ patient["transfer_count"] * len(query_patient_id)
		+ unique_room_count * unique_room_count
	)
	print(patient["current_room"], priority_score)
