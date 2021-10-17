import { Entity, Column, PrimaryGeneratedColumn } from 'typeorm';

@Entity()
export class Iot {
  @PrimaryGeneratedColumn('increment')
  id: number;

  @Column({ default: () => 'NOW()' })
  date: Date;

  @Column()
  name: string;

  @Column({ default: 0 })
  temperature: number;

  @Column({ default: 0 })
  humidity: number;

  @Column({ default: 0 })
  longitude: number;

  @Column({ default: 0 })
  latitude: number;

  @Column({ default: false })
  smoke: boolean;
}
